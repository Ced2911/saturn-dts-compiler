!
! from Benjamin Lee
!
	.global	_setjmp
_setjmp:
	.align 4
	mov.l  	r5,@-r15
	sts	pr,r5
	mov.l	r5,@r4
	add    	#0x04,r4
	mov.l	r0,@(0x00,r4)
	mov.l	r1,@(0x04,r4)
	mov.l	r2,@(0x08,r4)
	mov.l	r3,@(0x0c,r4)
	mov.l	r4,@(0x10,r4)
	mov.l	@r15,r5
	mov.l	r5,@(0x14,r4)
	mov.l	r6,@(0x18,r4)
	mov.l	r7,@(0x1c,r4)
	mov.l	r8,@(0x20,r4)
	mov.l	r9,@(0x24,r4)
	mov.l	r10,@(0x28,r4)
	mov.l	r11,@(0x2c,r4)
	mov.l	r12,@(0x30,r4)
	mov.l	r13,@(0x34,r4)
	mov.l	r14,@(0x38,r4)
	mov.l	r15,@(0x3c,r4)
	rts
	mov    #0,r0

	.global	_longjmp
_longjmp:
	mov.l	@(0x0,r4),r6
	lds	r6,pr
	add    	#0x04,r4
	mov.l		@(0x00,r4),r0
	mov.l		@(0x04,r4),r1
	mov.l		@(0x08,r4),r2
	mov.l		@(0x0c,r4),r3
	mov.l		@(0x18,r4),r6
	mov.l		@(0x1c,r4),r7
	mov.l		@(0x20,r4),r8
	mov.l		@(0x24,r4),r9
	mov.l		@(0x28,r4),r10
	mov.l		@(0x2c,r4),r11
	mov.l		@(0x30,r4),r12
	mov.l		@(0x34,r4),r13
	mov.l		@(0x38,r4),r14
	mov.l		@(0x3c,r4),r15
	tst	r5,r5
	mov.l  	r5,@-r15
	mov.l  		@(0x14,r4),r5
	mov.l	r15,@r4
	bf		HERE
	mov	#1,r4
HERE: 	rts
	mov	r4,r0

