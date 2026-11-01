#!/usr/bin/env python3
"""
A small permuter for the PSY-Q build.

Takes a function from src/*.c, applies random source-level mutations (operand order,
if/else shape, compound assignments, signedness, statement order, temporaries, ...),
rebuilds in parallel copies of the project and scores each result against the original
executable with check_match.py. Stops when a variant matches and prints it.

usage: permute.py SLUS_008.54 FUNC [--jobs 4] [--iters 400] [--seed N] [--apply]

ninja must be on PATH (or next to the python interpreter, e.g. inside the venv).
The function is edited in a throw-away copy of src/; with --apply the best variant is
written back into the real source file.
"""
import argparse
import os
import random
import re
import shutil
import subprocess
import sys
import tempfile
import threading

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from check_match import Checker  # noqa: E402

REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))

# ----------------------------------------------------------------------------
# locating the function

def find_function(name):
    for fn in sorted(os.listdir(os.path.join(REPO, "src"))):
        if not fn.endswith(".c"):
            continue
        path = os.path.join(REPO, "src", fn)
        text = open(path).read()
        m = re.search(r"^[\w][\w \*]*\b" + re.escape(name) + r"\([^;]*?\)\n\{\n", text, re.M)
        if not m:
            continue
        end = text.index("\n}\n", m.start()) + 3
        return path, text, m.start(), end
    sys.exit(f"function {name} not found")

# ----------------------------------------------------------------------------
# mutations (all text based; each returns the new text or None if not applicable)

COMM = r"(\+|\*|&|\||\^|==|!=)"
OPERAND = r"[\w\.]+(?:->\w+|\[[\w\+\- ]+\])*"


def m_commute(t, rnd):
    ms = list(re.finditer(r"(" + OPERAND + r") " + COMM + r" (" + OPERAND + r")(?![\w\[\.])", t))
    if not ms:
        return None
    m = rnd.choice(ms)
    return t[:m.start()] + f"{m.group(3)} {m.group(2)} {m.group(1)}" + t[m.end():]


FLIP = {"<": ">", ">": "<", "<=": ">=", ">=": "<="}


def m_relflip(t, rnd):
    ms = list(re.finditer(r"(" + OPERAND + r") (<=|>=|<|>) (" + OPERAND + r")", t))
    if not ms:
        return None
    m = rnd.choice(ms)
    return t[:m.start()] + f"{m.group(3)} {FLIP[m.group(2)]} {m.group(1)}" + t[m.end():]


NEG = {"<": ">=", ">": "<=", "<=": ">", ">=": "<", "==": "!=", "!=": "=="}


def negate(c):
    m = re.fullmatch(r"(.+?) (<=|>=|<|>|==|!=) (.+)", c)
    if m and "&&" not in c and "||" not in c:
        return f"{m.group(1)} {NEG[m.group(2)]} {m.group(3)}"
    m = re.fullmatch(r"!\((.+)\)", c)
    if m:
        return m.group(1)
    m = re.fullmatch(r"!(\w+)", c)
    if m:
        return m.group(1)
    return f"!({c})"


def m_ifelse(t, rnd):
    pats = list(re.finditer(r"( *)if \((.+)\)\n\1\{\n((?:.*\n)*?)\1\}\n\1else\n\1\{\n((?:.*\n)*?)\1\}\n", t))
    if not pats:
        return None
    m = rnd.choice(pats)
    ind, c, a, b = m.groups()
    new = f"{ind}if ({negate(c)})\n{ind}{{\n{b}{ind}}}\n{ind}else\n{ind}{{\n{a}{ind}}}\n"
    return t[:m.start()] + new + t[m.end():]


def m_early_return(t, rnd):
    # if (C) { return X; } return Y;   <->   if (!C) { return Y; } return X;
    pats = list(re.finditer(r"( *)if \((.+)\)\n\1\{\n\1    return (.+);\n\1\}\n\1return (.+);\n", t))
    if not pats:
        return None
    m = rnd.choice(pats)
    ind, c, x, y = m.groups()
    new = f"{ind}if ({negate(c)})\n{ind}{{\n{ind}    return {y};\n{ind}}}\n{ind}return {x};\n"
    return t[:m.start()] + new + t[m.end():]


COMPOUND = ["|", "&", "+", "-", "^", "<<", ">>"]


def m_compound(t, rnd):
    ms = list(re.finditer(r"(" + OPERAND + r") (\||&|\+|-|\^|<<|>>)= ([^;]+);", t))
    ms2 = list(re.finditer(r"(" + OPERAND + r") = \1 (\||&|\+|-|\^|<<|>>) ([^;]+);", t))
    if not ms and not ms2:
        return None
    if ms and (not ms2 or rnd.random() < 0.5):
        m = rnd.choice(ms)
        return t[:m.start()] + f"{m.group(1)} = {m.group(1)} {m.group(2)} {m.group(3)};" + t[m.end():]
    m = rnd.choice(ms2)
    return t[:m.start()] + f"{m.group(1)} {m.group(2)}= {m.group(3)};" + t[m.end():]


INT_TYPES = ["int", "unsigned int", "short", "unsigned short", "char", "unsigned char"]


def m_signed(t, rnd):
    # change the integer type of a local / parameter declaration
    ms = list(re.finditer(r"(?<![\w])(unsigned int|unsigned short|unsigned char|int|short|char)( \w+)(?=[,;\)]| =)", t))
    if not ms:
        return None
    m = rnd.choice(ms)
    new = rnd.choice([x for x in INT_TYPES if x != m.group(1)])
    return t[:m.start()] + new + m.group(2) + t[m.end():]


def m_swap_stmts(t, rnd):
    lines = t.split("\n")
    idx = [i for i in range(len(lines) - 1)
           if re.fullmatch(r" {4,}[^{}\s].*;", lines[i]) and re.fullmatch(r" {4,}[^{}\s].*;", lines[i + 1])
           and not lines[i].strip().startswith(("return", "break", "continue"))
           and not re.match(r" +(unsigned |signed )?(int|short|char|long|struct|Minion|Item)\b", lines[i])
           and not re.match(r" +(unsigned |signed )?(int|short|char|long|struct|Minion|Item)\b", lines[i + 1])
           and len(lines[i]) - len(lines[i].lstrip()) == len(lines[i + 1]) - len(lines[i + 1].lstrip())]
    if not idx:
        return None
    i = rnd.choice(idx)
    lines[i], lines[i + 1] = lines[i + 1], lines[i]
    return "\n".join(lines)


def m_swap_decls(t, rnd):
    lines = t.split("\n")
    idx = [i for i in range(len(lines) - 1)
           if re.fullmatch(r" {4}[\w\* ]+ \**\w+(\[\w+\])?( = [^;]+)?;", lines[i])
           and re.fullmatch(r" {4}[\w\* ]+ \**\w+(\[\w+\])?( = [^;]+)?;", lines[i + 1])
           and " = " not in lines[i] and " = " not in lines[i + 1]]
    if not idx:
        return None
    i = rnd.choice(idx)
    lines[i], lines[i + 1] = lines[i + 1], lines[i]
    return "\n".join(lines)


def m_index_form(t, rnd):
    ms = list(re.finditer(r"(\w+)\[(\w+)\]", t))
    ms2 = list(re.finditer(r"\*\((\w+) \+ (\w+)\)", t))
    if not ms and not ms2:
        return None
    if ms and (not ms2 or rnd.random() < 0.6):
        m = rnd.choice(ms)
        return t[:m.start()] + f"*({m.group(1)} + {m.group(2)})" + t[m.end():]
    m = rnd.choice(ms2)
    return t[:m.start()] + f"{m.group(1)}[{m.group(2)}]" + t[m.end():]


def m_arrow(t, rnd):
    ms = list(re.finditer(r"\b(\w+)->(\w+)", t))
    ms2 = list(re.finditer(r"\(\*(\w+)\)\.(\w+)", t))
    if not ms and not ms2:
        return None
    if ms and (not ms2 or rnd.random() < 0.7):
        m = rnd.choice(ms)
        return t[:m.start()] + f"(*{m.group(1)}).{m.group(2)}" + t[m.end():]
    m = rnd.choice(ms2)
    return t[:m.start()] + f"{m.group(1)}->{m.group(2)}" + t[m.end():]


TEMP_TYPES = ["int", "unsigned int", "short", "unsigned char", "char*", "int*"]


def m_temp(t, rnd):
    # hoist an rvalue like p->x / a[i] out of a statement into a new local
    body_start = t.index("{\n") + 2
    lines = t.split("\n")
    cand = []
    for i, ln in enumerate(lines):
        if i == 0 or not re.match(r" {4,}\S", ln) or ln.strip().startswith(("return", "if", "while", "for")):
            continue
        for m in re.finditer(r"(?<![\w\.>])(\w+->\w+|\w+\[\w+\])(?!\s*=[^=])", ln):
            cand.append((i, m))
    if not cand:
        return None
    i, m = rnd.choice(cand)
    ln = lines[i]
    indent = ln[:len(ln) - len(ln.lstrip())]
    name = f"tmp{rnd.randrange(100)}"
    ty = rnd.choice(TEMP_TYPES)
    lines[i] = ln[:m.start()] + name + ln[m.end():]
    lines.insert(i, f"{indent}{name} = {m.group(1)};")
    # declaration right after the opening brace of the function
    j = next(k for k, l in enumerate(lines) if l == "{")
    lines.insert(j + 1, f"    {ty} {name};")
    return "\n".join(lines)


def m_drop_temp(t, rnd):
    ms = list(re.finditer(r"\n +(tmp\d+) = ([^;]+);\n", t))
    if not ms:
        return None
    m = rnd.choice(ms)
    name, expr = m.group(1), m.group(2)
    rest = t[m.end():]
    if len(re.findall(r"\b" + name + r"\b", rest)) != 1:
        return None
    rest = re.sub(r"\b" + name + r"\b", lambda _: expr, rest, count=1)
    new = t[:m.start()] + "\n" + rest
    new = re.sub(r"\n +[\w\* ]+ " + name + r";", "", new, count=1)
    return new


def m_paren_cast(t, rnd):
    ms = list(re.finditer(r"\(unsigned int\)|\(int\)|\(unsigned\)", t))
    if ms and rnd.random() < 0.5:
        m = rnd.choice(ms)
        return t[:m.start()] + t[m.end():]
    ms = list(re.finditer(r"= (\w+)(?:->\w+)?;", t))
    if not ms:
        return None
    m = rnd.choice(ms)
    return t[:m.start()] + "= (int)" + t[m.start() + 2:]


MUTATIONS = [m_commute, m_relflip, m_ifelse, m_early_return, m_compound, m_signed, m_swap_stmts,
             m_swap_decls, m_index_form, m_arrow, m_temp, m_drop_temp, m_paren_cast]


def mutate(text, rnd):
    for _ in range(20):
        fn = rnd.choice(MUTATIONS)
        out = fn(text, rnd)
        if out and out != text:
            return out
    return text

# ----------------------------------------------------------------------------
# building

def make_worker_dir(root, idx):
    d = os.path.join(root, f"w{idx}")
    os.makedirs(d)
    for f in ("build.py", "linker_command_file.txt", "symbol_addrs.txt"):
        shutil.copy(os.path.join(REPO, f), d)
    shutil.copytree(os.path.join(REPO, "src"), os.path.join(d, "src"))
    os.symlink(os.path.join(REPO, "libs"), os.path.join(d, "libs"))
    os.makedirs(os.path.join(d, "build_psyq"))
    return d


def build(d):
    env = dict(os.environ)
    env["PATH"] = os.path.dirname(sys.executable) + os.pathsep + env.get("PATH", "")
    r = subprocess.run([sys.executable, "build.py"], cwd=d, env=env, stdout=subprocess.PIPE,
                       stderr=subprocess.STDOUT)
    return r.returncode == 0


class Shared:
    def __init__(self, text, score):
        self.best_text = text
        self.best_score = score
        self.lock = threading.Lock()
        self.done = threading.Event()
        self.tried = 0


def worker(idx, d, args, chk, fname, src_path, full_text, start, end, shared, base_seed):
    rnd = random.Random(base_seed * 1000 + idx)
    rel_src = os.path.join(d, "src", os.path.basename(src_path))
    while not shared.done.is_set():
        with shared.lock:
            if shared.tried >= args.iters:
                return
            shared.tried += 1
            n = shared.tried
            cur, cur_score = shared.best_text, shared.best_score
        cand = cur
        for _ in range(rnd.choice([1, 1, 1, 2, 3])):
            cand = mutate(cand, rnd)
        if cand == cur:
            continue
        open(rel_src, "w").write(full_text[:start] + cand + full_text[end:])
        if not build(d):
            continue
        chk.repo = d
        chk.reload()
        score = chk.check(fname)
        if score is None:
            continue
        with shared.lock:
            if score <= shared.best_score:
                if score < shared.best_score:
                    print(f"[{n}] score {score}", flush=True)
                shared.best_text, shared.best_score = cand, score
            if score == 0:
                shared.done.set()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("exe")
    ap.add_argument("func")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--iters", type=int, default=400)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--apply", action="store_true", help="write the best variant back to the source file")
    args = ap.parse_args()

    src_path, full_text, start, end = find_function(args.func)
    func_text = full_text[start:end]
    root = tempfile.mkdtemp(prefix="permute_")
    try:
        dirs = [make_worker_dir(root, i) for i in range(args.jobs)]
        # score the unmodified function first (each worker keeps its own checker state)
        base_dir = dirs[0]
        if not build(base_dir):
            sys.exit("baseline build failed")
        base_chk = Checker(args.exe, base_dir)
        base = base_chk.check(args.func)
        if base is None:
            sys.exit("function not in build (is it defined and does it have a symbol?)")
        print(f"baseline score: {base}")
        if base == 0:
            print("already matches")
            return
        shared = Shared(func_text, base)
        threads = []
        for i, d in enumerate(dirs):
            chk = Checker(args.exe, d, load=False)
            t = threading.Thread(target=worker, args=(i, d, args, chk, args.func, src_path, full_text, start,
                                                      end, shared, args.seed))
            t.start()
            threads.append(t)
        for t in threads:
            t.join()
        print(f"tried {shared.tried} variants, best score {shared.best_score}")
        print(shared.best_text)
        if args.apply and shared.best_score < base:
            open(src_path, "w").write(full_text[:start] + shared.best_text + full_text[end:])
            print(f"applied to {src_path}")
    finally:
        shutil.rmtree(root, ignore_errors=True)


if __name__ == "__main__":
    main()
