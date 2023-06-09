/* This is just like the default gvarargs.h
   except for differences described below.  */

/* Define __gnuc_va_list.  */

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST

/* start-sanitize-v9 */
#if defined (__sparc_v9__) && ! defined (__sparc_oldv9__)
/* This is the current proposal from the v9-abi committee.  */
typedef long long __va_greg;
typedef double __va_freg;
typedef struct {
  __va_greg * __va_next_o;		/* next available %o* register */
  __va_greg * __va_next_o_limit;	/* past last available %o* register */
  __va_freg * __va_next_fp;		/* next available %f* register */
  __va_freg * __va_next_fp_limit;	/* last available %f* register */
  __va_greg * __va_next_stack;		/* next extended word on stack */
} __gnuc_va_list;
#else
/* end-sanitize-v9 */
#ifndef __svr4__
/* This has to be a char * to be compatible with Sun.
   i.e., we have to pass a `va_list' to vsprintf.  */
typedef char * __gnuc_va_list;
#else
/* This has to be a void * to be compatible with Sun svr4.
   i.e., we have to pass a `va_list' to vsprintf.  */
typedef void * __gnuc_va_list;
#endif
/* start-sanitize-v9 */
#endif
/* end-sanitize-v9 */
#endif /* not __GNUC_VA_LIST */

/* If this is for internal libc use, don't define anything but
   __gnuc_va_list.  */
#if defined (_STDARG_H) || defined (_VARARGS_H)

#ifdef _STDARG_H

/* start-sanitize-v9 */
#if defined (__sparc_v9__) && ! defined (__sparc_oldv9__)
#define va_start(AP, LASTARG) \
__extension__ \
  ({ \
     AP.__va_next_o = (__va_greg *) __builtin_saveregs (); \
     AP.__va_next_o_limit = (AP.__va_next_o + \
			     (__builtin_args_info (0) < 6 ? 6 - __builtin_args_info (0) : 0)); \
     AP.__va_next_fp = (__va_freg *) AP.__va_next_o_limit; \
     AP.__va_next_fp_limit = (AP.__va_next_fp + \
			      (__builtin_args_info (1) < 16 ? (16 - __builtin_args_info (1) + 1) / 2 : 0)); \
     AP.__va_next_stack = (__va_greg *) __builtin_next_arg(); \
  })
#else
/* end-sanitize-v9 */
#ifdef __GCC_NEW_VARARGS__
#define va_start(AP, LASTARG)	(AP = (char *) __builtin_saveregs ())
#else
#define va_start(AP, LASTARG)					\
  (__builtin_saveregs (), AP = ((char *) __builtin_next_arg ()))
#endif
/* start-sanitize-v9 */
#endif
/* end-sanitize-v9 */

#else

#define va_alist  __builtin_va_alist
#define va_dcl    int __builtin_va_alist;

/* start-sanitize-v9 */
#if defined (__sparc_v9__) && ! defined (__sparc_oldv9__)
#define va_start(AP) \
__extension__ \
  ({ \
     AP.__va_next_o = (__va_greg *) __builtin_saveregs (); \
     AP.__va_next_o_limit = (AP.__va_next_o + \
			     (__builtin_args_info (0) < 6 ? 6 - __builtin_args_info (0) : 0)); \
     AP.__va_next_fp = (__va_freg *) AP.__va_next_o_limit; \
     AP.__va_next_fp_limit = (AP.__va_next_fp + \
			      (__builtin_args_info (1) < 16 ? (16 - __builtin_args_info (1) + 1) / 2 : 0)); \
     AP.__va_next_stack = (__va_greg *) __builtin_next_arg(); \
  })
#else
/* end-sanitize-v9 */
#ifdef __GCC_NEW_VARARGS__
#define va_start(AP)		((AP) = (char *) __builtin_saveregs ())
#else
#define va_start(AP) 						\
 (__builtin_saveregs (), (AP) = ((char *) &__builtin_va_alist))
#endif
/* start-sanitize-v9 */
#endif
/* end-sanitize-v9 */

#endif

#ifndef va_end
void va_end (__gnuc_va_list);		/* Defined in libgcc.a */

/* Values returned by __builtin_classify_type.  */

enum __va_type_classes {
  __no_type_class = -1,
  __void_type_class,
  __integer_type_class,
  __char_type_class,
  __enumeral_type_class,
  __boolean_type_class,
  __pointer_type_class,
  __reference_type_class,
  __offset_type_class,
  __real_type_class,
  __complex_type_class,
  __function_type_class,
  __method_type_class,
  __record_type_class,
  __union_type_class,
  __array_type_class,
  __string_type_class,
  __set_type_class,
  __file_type_class,
  __lang_type_class
};

#endif
#define va_end(pvar)

/* start-sanitize-v9 */
#ifdef __sparc_v9__
#ifdef __sparc_oldv9__
/* ??? This must round to the same boundary as PARM_BOUNDARY.
   Unfortunately, there is no type that is safe to use, like there is for
   the v7 case, so for now just hardwire in 8 which is always correct
   for the v9 case.  */
#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + 7) / 8) * 8)
#endif
#else  
/* end-sanitize-v9 */
#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))
/* start-sanitize-v9 */
#endif
/* end-sanitize-v9 */

/* Avoid errors if compiling GCC v2 with GCC v1.  */
#if __GNUC__ == 1
#define __extension__
#endif

/* RECORD_TYPE args passed using the C calling convention are
   passed by invisible reference.  ??? RECORD_TYPE args passed
   in the stack are made to be word-aligned; for an aggregate that is
   not word-aligned, we advance the pointer to the first non-reg slot.  */

/* start-sanitize-v9 */
#if defined (__sparc_v9__) && ! defined (__sparc_oldv9__)

#define va_arg(pvar,TYPE)					\
__extension__							\
({int __type = __builtin_classify_type (* (TYPE *) 0);		\
  void * __result;						\
  if (__type == __real_type_class)		/* float? */	\
    {								\
      __va_freg *__r;						\
      /* see PASS_IN_REG_P in sparc64-v9-abi.h */		\
      if (pvar.__va_next_fp < pvar.__va_next_fp_limit		\
	  && ((__r = (__va_freg *) (((long long) pvar.__va_next_fp + sizeof (TYPE) - 1) & ~(long long) (sizeof (TYPE) - 1))) \
	      < pvar.__va_next_fp_limit))			\
	{							\
	  pvar.__va_next_fp = __r + sizeof (TYPE) / 8;		\
	}							\
      else							\
	{							\
	  __r = (__va_freg *) pvar.__va_next_stack;		\
	  pvar.__va_next_stack += sizeof (TYPE) / 8;		\
	}							\
      __result = __r;						\
    }								\
  else if (__type < __record_type_class)	/* integer? */	\
    {								\
      __va_greg *__r;						\
      if (pvar.__va_next_o < pvar.__va_next_o_limit)		\
	__r = pvar.__va_next_o++;				\
      else							\
	__r = pvar.__va_next_stack++;				\
      __result = (char *) __r + 8 - sizeof (TYPE);	/* adjust for 4 byte ints */ \
    }								\
  else /* aggregate object */					\
    {								\
      void **__r;						\
      if (pvar.__va_next_o < pvar.__va_next_o_limit)		\
	__r = *(void **) pvar.__va_next_o++;			\
      else							\
	__r = *(void **) pvar.__va_next_stack++;		\
      __result = *__r;						\
    }								\
  *(TYPE *) __result;})

#else /* ! __sparc_v9__ */

#ifdef __sparc_oldv9__
#define va_arg(pvar,TYPE)					\
__extension__							\
({((__builtin_classify_type (* (TYPE *) 0) >= __record_type_class) \
    ? ((pvar) += __va_rounded_size (TYPE *),			\
       **(TYPE **) (void *) ((pvar) - sizeof (TYPE *)))		\
    : ((pvar) += __va_rounded_size (TYPE),			\
       *((TYPE *) (void *) ((pvar) - sizeof (TYPE)))));})
#else
/* end-sanitize-v9 */
/* We don't declare the union member `d' to have type TYPE
   because that would lose in C++ if TYPE has a constructor.  */
/* We cast to void * and then to TYPE * because this avoids
   a warning about increasing the alignment requirement.
   The casts to char * avoid warnings about invalid pointer arithmetic.  */
#define va_arg(pvar,TYPE)					\
__extension__							\
({ TYPE __va_temp;						\
   ((__builtin_classify_type (__va_temp) >= __record_type_class) \
    ? ((pvar) = (char *)(pvar) + __va_rounded_size (TYPE *),	\
       **(TYPE **) (void *) ((char *)(pvar) - __va_rounded_size (TYPE *))) \
    : __va_rounded_size (TYPE) == 8				\
    ? ({ union {char __d[sizeof (TYPE)]; int __i[2];} __u;	\
	 __u.__i[0] = ((int *) (void *) (pvar))[0];		\
	 __u.__i[1] = ((int *) (void *) (pvar))[1];		\
	 (pvar) = (char *)(pvar) + 8;				\
	 *(TYPE *) (void *) __u.__d; })				\
    : ((pvar) = (char *)(pvar) + __va_rounded_size (TYPE),	\
       *((TYPE *) (void *) ((char *)(pvar) - __va_rounded_size (TYPE)))));})
/* start-sanitize-v9 */
#endif /* ! __sparc_oldv9__ */
#endif /* __sparc_v9__ && ! __sparc_oldv9__ */
/* end-sanitize-v9 */

#endif /* defined (_STDARG_H) || defined (_VARARGS_H) */
