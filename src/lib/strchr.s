# index/rindex (strchr/strrchr) as linked into the game: no PSY-Q release we have has this copy
# (no alignment padding behind it), so it is assembly here.
	.set	noreorder
	.set	noat
	.text
# char *index(char *s, int c) (strchr)
	.globl	index
index:
	beq	$4,$0,L80071AAC
	sll	$2,$5,0x18
	sra	$2,$2,0x18
L80071A94:
	lb	$3,0($4)
	nop
	beq	$3,$2,L80071AB4
	nop
	bne	$3,$0,L80071A94
	addiu	$4,$4,1
L80071AAC:
	j	L80071AB8
	addu	$2,$0,$0
L80071AB4:
	addu	$2,$4,$0
L80071AB8:
	jr	$31
	nop

# char *rindex(char *s, int c)
rindex:
	beq	$4,$0,L80071B00
	addu	$6,$4,$0
L80071AC8:
	lb	$2,0($4)
	nop
	bne	$2,$0,L80071AC8
	addiu	$4,$4,1
	addiu	$4,$4,-1
	sll	$2,$5,0x18
	sra	$3,$2,0x18
L80071AE4:
	lb	$2,0($4)
	nop
	beq	$2,$3,L80071B04
	addu	$2,$4,$0
	sltu	$2,$6,$2
	bne	$2,$0,L80071AE4
	addiu	$4,$4,-1
L80071B00:
	addu	$2,$0,$0
L80071B04:
	jr	$31
	nop

# the stack size the SN start-up (2MBYTE.OBJ) gives the main thread
	.section	.rdata
	.globl	_stacksize
_stacksize:
	.word	0x00004000
	.text
