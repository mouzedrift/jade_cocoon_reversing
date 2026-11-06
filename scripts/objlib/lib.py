"""PSY-Q .LIB archives"""
import struct


def lib_modules(path):
    """(module name, obj bytes) of a PSY-Q .LIB"""
    data = open(path, "rb").read()
    assert data[:4] == b"LIB\x01", path
    pos = 4
    while pos < len(data):
        name = data[pos:pos + 8].decode().strip()
        hdr, size = struct.unpack("<II", data[pos + 12:pos + 20])
        yield name, data[pos + hdr:pos + size]
        pos += size
