
!
! Fast SH memcpy
!
! by Toshiyasu Morita (tm@netcom.com)
!
! Entry: r4: destination pointer
!        r5: source pointer
!        r6: byte count
!
! Exit:  r0-r3: trashed
!
! Notes: Usually one wants to do small reads and write a longword, but
!        unfortunately it is difficult to concatanate bytes into a longword
!        on the SH, so this does a longword read and small writes.
!

	.text
	.align	2
	.global	_new_memcpy
_qmemcpy:
	mov	r4,r3	! Save return value

	mov	#0,r0	! Check explicitly for zero
	cmp/eq	r0,r6
	bt	L_exit

	mov	#12,r0	! Check if small number of bytes
	cmp/gt	r0,r6
	bf	L_cleanup_loop

	neg	r5,r0	! Calculate bytes needed to align source
	add	#4,r0
	and	#3,r0
	tst	r0,r0
	bt	L_jump
	mov	r0,r1

!	.align	2
L_loop1:
	mov.b	@r5+,r0	! Copy bytes to align source
	dt	r1
	mov.b	r0,@r4
	add	#-1,r6
	add	#1,r4
	bf	L_loop1

L_jump:
	mov	r6,r2	! Calculate number of longwords to copy
	shlr2	r2
	tst	r2,r2
	bt	L_cleanup

	mov	r4,r0	! Jump to appropriate routine
	and	#3,r0
	mov	r0,r1
	mova	L_offset_tbl,r0
	mov.b	@(r0,r1),r1
	add	r1,r0
	jmp	@r0
	nop

	.align	2
L_offset_tbl:
	.byte	L_dest00-L_offset_tbl
	.byte	L_dest01-L_offset_tbl
	.byte	L_dest10-L_offset_tbl
	.byte	L_dest11-L_offset_tbl

! Destination = 00

	.align	2
L_dest00:
	mov.l	@r5+,r0	! Read longword, write longword per iteration
	dt	r2
	mov.l	r0,@r4
	add	#4,r4
	bf	L_dest00

	bra	L_cleanup
	nop
	
! Destination = 10

	.align	2
L_dest10:
	mov.l	@r5+,r0	! Read longword, write two words per iteration
	dt	r2
#ifdef __LITTLE_ENDIAN__
	mov.w	r0,@r4
	shlr16	r0
	mov.w	r0,@(2,r4)
#else
	mov.w	r0,@(2,r4)
	shlr16	r0
	mov.w	r0,@r4
#endif
	add	#4,r4
	bf	L_dest10

	bra	L_cleanup
	nop

! Destination = 01 or 11

	.align	2
L_dest01:
L_dest11:
	mov.l	@r5+,r0	! Read longword, write byte, word, byte per iteration
	dt	r2
#if __LITTLE_ENDIAN__
	mov.b	r0,@r4
	shlr8	r0
	mov.b	r0,@(1,r4)	! mov.w r0,@(1,r4) is illegal
	shlr8	r0
	mov.b	r0,@(2,r4)
	shlr8	r0
	mov.b	r0,@(3,r4)
#else
	mov.b	r0,@(3,r4)
	shlr8	r0
	mov.b	r0,@(2,r4)	! mov.w r0,@(1,r4) is illegal
	shlr8	r0
	mov.b	r0,@(1,r4)
	shlr8	r0
	mov.b	r0,@r4
#endif
	add	#4,r4
	bf	L_dest11

! Cleanup last few bytes

	.align	2
L_cleanup:
	mov	r6,r0
	and	#3,r0
	tst	r0,r0
	bt	L_exit
	mov	r0,r6

!	.align	2
L_cleanup_loop:
	mov.b	@r5+,r0
	dt	r6
	mov.b	r0,@r4
	add	#1,r4
	bf	L_cleanup_loop

L_exit:
	rts
	mov	r3,r0	! return dest

