	.file	"hello.c"
	.data

! Hitachi SH cc1 (cygnus-2.5.90-940226) (release C-1) arguments: -O -g
! -fdefer-pop -fomit-frame-pointer -fthread-jumps -fpeephole -ffunction-cse
! -finline -freg-struct-return -fdelayed-branch -fcommon -fgnu-linker

! 1010 505
gcc2_compiled.:
___gnu_compiled_c:
	.text
	.align 2
LC0:
	.ascii "Hello World %d\12\0"
	.align 1
	.def	_main;	.val	_main;	.scl	2;	.type	044;	.endef
	.global	_main
_main:
	mov.l	r8,@-r15
	mov.l	r9,@-r15
	sts.l	pr,@-r15 ! push
	.def	.bf;	.val	.;	.scl	101;	.line	3;	.endef
	.ln	2
	.def	.bb;	.val	.;	.scl	100;	.line	2;	.endef
	.def	_i;	.val	8;	.scl	4;	.type	04;	.endef
	.ln	3
	mov	#0,r8
	mov.l	L6,r9
L5:
	.ln	4
	mov.l	L7,r4
	jsr	@r9
	mov	r8,r5
	.ln	3
	add	#1,r8
	mov	#9,r1
	cmp/gt	r1,r8
	bf	L5
	.ln	5
	mov	#0,r0
	.ln	6
	.def	.eb;	.val	.;	.scl	100;	.line	6;	.endef
	lds.l	@r15+,pr
	mov.l	@r15+,r9
	rts	
	mov.l	@r15+,r8
	.align 2
L6:
	.long	_iprintf
L7:
	.long	LC0
	.def	.ef;	.val	.;	.scl	101;	.line	6;	.endef
	.def	_main;	.val	.;	.scl	-1;	.endef
