      .global _setjmp
      .align 2
_setjmp:
      add     #(18*4),r4

      mov     #-1,r5          ! stick ffff at end of table
      mov.l   r5,@-r4

      sts.l   pr,@-r4

      mov.l   r15,@-r4
      mov.l   r14,@-r4
      mov.l   r13,@-r4
      mov.l   r12,@-r4

      mov.l   r11,@-r4
      mov.l   r10,@-r4
      mov.l   r9,@-r4
      mov.l   r8,@-r4

      mov.l   r7,@-r4
      mov.l   r6,@-r4
      mov.l   r5,@-r4
      mov.l   r4,@-r4

      mov.l   r3,@-r4
      mov.l   r2,@-r4
      mov.l   r1,@-r4
      mov.l   r0,@-r4
      rts
      mov    #0,r0

      .global _longjmp
_longjmp:
      mov.l   @r4+,r0
      mov.l   @r4+,r1
      mov.l   @r4+,r2
      mov.l   @r4+,r3

      mov.l   @r4+,r6 ! do not clobber r4
      mov.l   @r4+,r6 ! and r5
      mov.l   @r4+,r6
      mov.l   @r4+,r7

      mov.l   @r4+,r8
      mov.l   @r4+,r9
      mov.l   @r4+,r10
      mov.l   @r4+,r11

      mov.l   @r4+,r12
      mov.l   @r4+,r13
      mov.l   @r4+,r14
      mov.l   @r4+,r15

      lds.l   @r4+,pr

      tst     r5,r5           ! set T bit from r5==0
      bf      retr4
      mov     #1,r5
retr4:        rts
      mov     r5,r0

