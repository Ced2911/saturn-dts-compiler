
#define sleep() 	{ asm ("sleep"); }
#define tas(addr) 	{ asm ("tas.b %0" : : "m" (addr)); }
#define trap(n) 	{ asm ("trapa  %0" : : "i" (n));}
#define set_cr(cr)   	{ asm ("ldc	%0,sr" :  : "r" (cr)); }
#define get_cr()   	({ int x; asm ("stc sr,%0" : "=r" (x)   ) ; x;})
#define get_imask() 	((get_cr() >> 4) & 0xf)
#define set_imask(x) 	{ int sr = get_cr(); sr &= 0xf0; sr |= x<< 4;  set_cr(sr);}
#define set_vbr(vbr) 	{ asm ("ldc	%0,vbr" :  : "r" (vbr)); }
#define get_vbr ()  	({ int vbr; asm ("stc vbr,%0" : "=r" (vbr)   ) ; vbr;})
#define set_gbr(gbr) 	{ asm ("ldc	%0,gbr" :  : "r" (gbr)); }
#define get_gbr ()  	({ int gbr; asm ("stc gbr,%0" : "=r" (gbr)   ) ; gbr;})

#define gbr_read_byte(offset) \
  ({ int x; asm  ("mov.b 	@(%O1,gbr),r0\n\tmov	r0,%0" : "=r" (x) : "i" (offset) : "r0") ; x;})

#define gbr_read_word(offset) \
  ({ int x; asm  ("mov.w 	@(%O1,gbr),r0\n\tmov	r0,%0" : "=r" (x) : "i" (offset) : "r0") ; x;})

#define gbr_read_long(offset)  \
     ({ int x; asm  ("mov.l 	@(%O1,gbr),r0\n\tmov	r0,%0" : "=r" (x) : "i" (offset) : "r0") ; x;})

#define gbr_write_byte(offset, data)  \
   { asm("mov.b	%0,@(%O1,gbr)" : : "z" (data), "i" (offset)); }

#define gbr_write_byte(offset, data)  \
   { asm("mov.b	%0,@(%O1,gbr)" : : "z" (data), "i" (offset)); }

#define gbr_write_word(offset, data)  \
   { asm("mov.w	%0,@(%O1,gbr)" : : "z" (data), "i" (offset)); }

#define gbr_write_long(offset, data)  \
   { asm("mov.l	%0,@(%O1,gbr)" : : "z" (data), "i" (offset)); }

#define gbr_and_byte(offset, mask) \
   { asm("and.b	%0,@(%1,gbr)" : : "i" (mask), "z" (offset)); }

#define gbr_or_byte(offset, mask) \
   { asm("or.b	%0,@(%1,gbr)" : : "i" (mask), "z" (offset)); }

#define gbr_xor_byte(offset, mask) \
   { asm("xor.b	%0,@(%1,gbr)" : : "i" (mask), "z" (offset)); }

#define gbr_tst_byte(offset, mask) \
   { asm("tst.b	%0,@(%1,gbr)" : : "i" (mask), "z" (offset)); }
