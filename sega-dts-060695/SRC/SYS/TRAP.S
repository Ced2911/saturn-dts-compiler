
	.text
	.global	__trap3
	.global	___trap3
__trap3:
___trap3:
	trapa #3
	
	tst	r1,r1	! r1 is errno
	bt	ret
	mov.l	perrno,r2
	mov.l	r2,@r1
ret:
	rts
	nop
	
perrno:
	.long	_errno
