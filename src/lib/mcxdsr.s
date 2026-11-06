# LIBMCX MCXDSR (_mcxStartFastDsr / _mcxStopFastDsr / _mcxFastDsrEnt), as linked into the game: no PSY-Q
# release we have carries this version of the module, so it is assembly here (relocatable, see build.py).
# _mcxStartFastDsr saves 3 words of the BIOS exception vector (B0 table entry 0x56 + 0x70) and patches in
# mcxDsrHook (a jump to _mcxFastDsrEnt); _mcxStopFastDsr puts them back.
# mcxDsrState: [0] patched vector, [1] saved $ra, [2..5] the arguments of _mcxStartFastDsr
	.set	noreorder
	.set	noat
	.text
	.globl	_mcxStartFastDsr
_mcxStartFastDsr:
	lui	$1,%hi(mcxDsrState+4)
	sw	$31,%lo(mcxDsrState+4)($1)
	lui	$1,%hi(index)
	sw	$0,%lo(index)($1)
	lui	$1,%hi(mcxDsrState+8)
	sw	$4,%lo(mcxDsrState+8)($1)
	lui	$1,%hi(mcxDsrState+12)
	sw	$5,%lo(mcxDsrState+12)($1)
	lui	$1,%hi(mcxDsrState+16)
	sw	$6,%lo(mcxDsrState+16)($1)
	lui	$1,%hi(mcxDsrState+20)
	sw	$7,%lo(mcxDsrState+20)($1)
	addiu	$9,$0,0x56
	addiu	$10,$0,0xb0
	jalr	$10
	nop
	lw	$2,0x18($2)
	nop
	addiu	$2,$2,0x70
	lui	$1,%hi(mcxDsrState)
	sw	$2,%lo(mcxDsrState)($1)
	lui	$10,%hi(mcxDsrSaved)
	addiu	$10,$10,%lo(mcxDsrSaved)
	lui	$9,%hi(mcxDsrSavedEnd)
	addiu	$9,$9,%lo(mcxDsrSavedEnd)
L8007187C:
	lw	$3,0($2)
	nop
	sw	$3,0($10)
	addiu	$10,$10,4
	bne	$10,$9,L8007187C
	addiu	$2,$2,4
	lui	$2,%hi(mcxDsrState)
	lw	$2,%lo(mcxDsrState)($2)
	lui	$10,%hi(mcxDsrHook)
	addiu	$10,$10,%lo(mcxDsrHook)
	lui	$9,%hi(mcxDsrHookEnd)
	addiu	$9,$9,%lo(mcxDsrHookEnd)
L800718AC:
	lw	$3,0($10)
	nop
	sw	$3,0($2)
	addiu	$10,$10,4
	bne	$10,$9,L800718AC
	addiu	$2,$2,4
	jal	FlushCache
	nop
	lui	$31,%hi(mcxDsrState+4)
	lw	$31,%lo(mcxDsrState+4)($31)
	nop
	jr	$31
	nop
	.globl	_mcxStopFastDsr
_mcxStopFastDsr:
	lui	$1,%hi(mcxDsrState+4)
	sw	$31,%lo(mcxDsrState+4)($1)
	lui	$2,%hi(mcxDsrState)
	lw	$2,%lo(mcxDsrState)($2)
	nop
	beq	$2,$0,L8007192C
	nop
	lui	$10,%hi(mcxDsrSaved)
	addiu	$10,$10,%lo(mcxDsrSaved)
	lui	$9,%hi(mcxDsrSavedEnd)
	addiu	$9,$9,%lo(mcxDsrSavedEnd)
L8007190C:
	lw	$3,0($10)
	nop
	sw	$3,0($2)
	addiu	$10,$10,4
	bne	$10,$9,L8007190C
	addiu	$2,$2,4
	jal	FlushCache
	nop
L8007192C:
	lui	$31,%hi(mcxDsrState+4)
	lw	$31,%lo(mcxDsrState+4)($31)
	nop
	jr	$31
	nop
mcxDsrHook:
	lui	$2,%hi(_mcxFastDsrEnt)
	addiu	$2,$2,%lo(_mcxFastDsrEnt)
	jalr	$2
	nop
mcxDsrHookEnd:
	nop
mcxDsrSaved:
	nop
	nop
	nop
mcxDsrSavedEnd:
	nop
	.globl	_mcxFastDsrEnt
_mcxFastDsrEnt:
	lui	$2,%hi(mcxDsrState+16)
	lw	$2,%lo(mcxDsrState+16)($2)
	nop
	beq	$2,$0,mcxFastDsrExit
	nop
	lui	$3,0x1f80
	lw	$2,0x1070($3)
	nop
	andi	$2,$2,0x80
	beq	$2,$0,mcxFastDsrExit
	nop
	lui	$2,%hi(mcxDsrState+8)
	lw	$2,%lo(mcxDsrState+8)($2)
	nop
	beq	$2,$0,L800719D0
	nop
	lbu	$0,0x1040($3)
	lui	$11,%hi(mcxDsrState+12)
	lw	$11,%lo(mcxDsrState+12)($11)
	nop
	lbu	$2,0($11)
	nop
	sb	$2,0x1040($3)
	addiu	$11,$11,1
	lui	$1,%hi(mcxDsrState+12)
	j	L800719F0
	sw	$11,%lo(mcxDsrState+12)($1)
L800719D0:
	lui	$11,%hi(mcxDsrState+12)
	lw	$11,%lo(mcxDsrState+12)($11)
	lbu	$2,0x1040($3)
	sb	$0,0x1040($3)
	sb	$2,0($11)
	addiu	$11,$11,1
	lui	$1,%hi(mcxDsrState+12)
	sw	$11,%lo(mcxDsrState+12)($1)
L800719F0:
	addiu	$11,$0,-0x81
	sw	$11,0x1070($3)
	lhu	$11,0x104a($3)
	nop
	ori	$11,$11,0x10
	sh	$11,0x104a($3)
	lui	$3,%hi(mcxDsrState+20)
	lw	$3,%lo(mcxDsrState+20)($3)
	nop
	lb	$11,0($3)
	nop
	xor	$11,$11,$2
	sb	$11,0($3)
	lui	$11,%hi(mcxDsrState+16)
	lhu	$11,%lo(mcxDsrState+16)($11)
	nop
	addiu	$11,$11,-1
	lui	$1,%hi(mcxDsrState+16)
	j	L80071A48
	sh	$11,%lo(mcxDsrState+16)($1)
mcxFastDsrExit:
	jr	$31
	nop
L80071A48:
	addiu	$11,$0,0x100
	lw	$11,8($11)
	nop
	lw	$11,0($11)
	nop
	addi	$11,$11,8
	lw	$2,8($11)
	lw	$3,0xc($11)
	lw	$31,0x7c($11)
	lw	$1,4($11)
	lw	$11,0x80($11)
	nop
	jr	$11
	.word	0x42000010
	nop
	nop
	.section	.data
mcxDsrState:
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.text
