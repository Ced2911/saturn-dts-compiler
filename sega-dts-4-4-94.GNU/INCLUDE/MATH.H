/*
	math.h
	Definitions for the math floating point package.
*/

#ifndef  _MATH_H_
#ifdef __cplusplus
extern "C" {
#endif
#define  _MATH_H_

#include <sys/reent.h>
#include <_ansi.h>

/* largest mag represent as  double */
#ifdef  _DOUBLE_IS_32BITS
#ifndef HUGE_VAL
#define HUGE_VAL 	3.40282347E+38
#endif
#else
#ifndef HUGE_VAL
#define HUGE_VAL	1.7976931348623157E+308	
#endif
#endif

#ifndef _REENT_ONLY
double	_EXFUN(acos  ,(double x));
double	_EXFUN(asin  ,(double x));
double	_EXFUN(cos   ,(double x));
double	_EXFUN(sin   ,(double x));
double	_EXFUN(tan   ,(double x));
double	_EXFUN(cosh  ,(double x));
double	_EXFUN(sinh  ,(double x));
double	_EXFUN(tanh  ,(double x));
double	_EXFUN(exp   ,(double x));
double	_EXFUN(log1p ,(double x));
double	_EXFUN(frexp ,(double x, int *exp));
double	_EXFUN(ldexp ,(double x, int exp));
double	_EXFUN(log   ,(double x));
double	_EXFUN(log10 ,(double x));
double	_EXFUN(log2 ,(double x));
double	_EXFUN(pow   ,(double x, double y));
double	_EXFUN(sqrt  ,(double x));
double	_EXFUN(cbrt  ,(double x));
double	_EXFUN(fmod  ,(double x, double y));
double	_EXFUN(atanh, (double x));
double	_EXFUN(acosh, (double x));
double	_EXFUN(asinh, (double x));
double	_EXFUN(remainder, (double x, double y));
#endif
#ifndef _STRICT_ANSI
double	_EXFUN(_acos_r  ,(struct _reent *, double x));
double	_EXFUN(_asin_r  ,(struct _reent *, double x));
double	_EXFUN(atan  ,(double x));
double	_EXFUN(atan2 ,(double y, double x));
double	_EXFUN(_cos_r   ,(struct _reent *, double x));
double	_EXFUN(_sin_r   ,(struct _reent *, double x));
double	_EXFUN(_tan_r   ,(struct _reent *, double x));
double	_EXFUN(_cosh_r  ,(struct _reent *, double x));
double	_EXFUN(_sinh_r  ,(struct _reent *, double x));
double	_EXFUN(_tanh_r  ,(struct _reent *, double x));
double	_EXFUN(_exp_r   ,(struct _reent *, double x));
double	_EXFUN(_log1p_r ,(struct _reent *, double x));
double	_EXFUN(_frexp_r ,(struct _reent *, double x, int *exp));
double	_EXFUN(_ldexp_r ,(struct _reent *, double x, int exp));
double	_EXFUN(_log_r   ,(struct _reent *, double x));
double	_EXFUN(_log10_r ,(struct _reent *, double x));
double	_EXFUN(_log2_r ,(struct _reent *, double x));
double	_EXFUN(modf  ,(double x, double *ipart));
double	_EXFUN(_pow_r   ,(struct _reent *, double x, double y));
double	_EXFUN(_sqrt_r  ,(struct _reent *, double x));
double	_EXFUN(_cbrt_r  ,(struct _reent *, double x));
double	_EXFUN(ceil  ,(double x));
double	_EXFUN(expm1  ,(double x));
double	_EXFUN(fabs  ,(double x));
double	_EXFUN(floor ,(double x));
double	_EXFUN(_fmod_r  ,(struct _reent *, double x, double y));
double	_EXFUN(_atanh_r, (struct _reent *, double x));
double	_EXFUN(_acosh_r, (struct _reent *, double x));
double	_EXFUN(_asinh_r, (struct _reent *, double x));
double	_EXFUN(_remainder_r, (struct _reent *, double x, double y));
#endif

#ifndef _STRICT_ANSI
/* Additions */ 

#ifndef _REENT_ONLY
_FLOAT_RET _EXFUN(acosf, (_FLOAT_ARG));
_FLOAT_RET _EXFUN(asinf, (_FLOAT_ARG));
_FLOAT_RET _EXFUN(cosf , (_FLOAT_ARG));
_FLOAT_RET _EXFUN(sinf , (_FLOAT_ARG));
_FLOAT_RET _EXFUN(tanf , (_FLOAT_ARG));
_FLOAT_RET _EXFUN(log1pf , (_FLOAT_ARG));
_FLOAT_RET _EXFUN(coshf, (_FLOAT_ARG));
_FLOAT_RET _EXFUN(sinhf, (_FLOAT_ARG));
_FLOAT_RET _EXFUN(tanhf, (_FLOAT_ARG));
_FLOAT_RET _EXFUN(expf,   (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(frexpf, (_FLOAT_ARG x, int *exp));
_FLOAT_RET _EXFUN(ldexpf, (_FLOAT_ARG x, int exp));
_FLOAT_RET _EXFUN(logf,   (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(log10f, (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(log2f, (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(powf,   (_FLOAT_ARG x, _FLOAT_ARG y));
_FLOAT_RET _EXFUN(sqrtf,  (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(cbrtf,  (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(fmodf, (_FLOAT_ARG x, _FLOAT_ARG y));
_FLOAT_RET _EXFUN(atanhf, (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(asinhf, (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(acoshf, (_FLOAT_ARG x));
#endif
_FLOAT_RET _EXFUN(_acosf_r, (struct _reent *, _FLOAT_ARG));
_FLOAT_RET _EXFUN(_asinf_r, (struct _reent *, _FLOAT_ARG));
_FLOAT_RET _EXFUN(atanf, (_FLOAT_ARG));
_FLOAT_RET _EXFUN(atan2f,(_FLOAT_ARG, _FLOAT_ARG));
_FLOAT_RET _EXFUN(_cosf_r , (struct _reent *, _FLOAT_ARG));
_FLOAT_RET _EXFUN(_sinf_r , (struct _reent *, _FLOAT_ARG));
_FLOAT_RET _EXFUN(_tanf_r , (struct _reent *, _FLOAT_ARG));
_FLOAT_RET _EXFUN(expm1f , (_FLOAT_ARG));
_FLOAT_RET _EXFUN(_log1pf_r , (struct _reent *, _FLOAT_ARG));
_FLOAT_RET _EXFUN(_coshf_r, (struct _reent *, _FLOAT_ARG));
_FLOAT_RET _EXFUN(_sinhf_r, (struct _reent *, _FLOAT_ARG));
_FLOAT_RET _EXFUN(_tanhf_r, (struct _reent *, _FLOAT_ARG));
_FLOAT_RET _EXFUN(_expf_r,   (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_frexpf_r, (struct _reent *, _FLOAT_ARG x, int *exp));
_FLOAT_RET _EXFUN(_ldexpf_r, (struct _reent *, _FLOAT_ARG x, int exp));
_FLOAT_RET _EXFUN(_logf_r,   (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_log10f_r, (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_log2f_r, (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(modff,  (_FLOAT_ARG x, float *ipart));
_FLOAT_RET _EXFUN(_powf_r,   (struct _reent *, _FLOAT_ARG x, _FLOAT_ARG y));
_FLOAT_RET _EXFUN(_sqrtf_r,  (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_cbrtf_r,  (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(ceilf,  (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(fabsf,  (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(floorf, (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(_fmodf_r, (struct _reent *, _FLOAT_ARG x, _FLOAT_ARG y));
_FLOAT_RET _EXFUN(_atanhf_r, (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_asinhf_r, (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_acoshf_r, (struct _reent *, _FLOAT_ARG x));

#ifndef _REENT_ONLY
double _EXFUN(gamma, (double x));
_FLOAT_RET _EXFUN(gammaf, (_FLOAT_ARG x));
#define signgam (_REENT->_signgam)
#ifdef SYSV
#define lgamma gamma
#endif
#endif
double _EXFUN(_gamma_r, (struct _reent *, double x));
_FLOAT_RET _EXFUN(_gammaf_r, (struct _reent *, _FLOAT_ARG x));

#ifndef _REENT_ONLY
double _EXFUN(erf,(double x));
double _EXFUN(erfc,(double x));
_FLOAT_RET _EXFUN(erff,(_FLOAT_ARG x));
_FLOAT_RET _EXFUN(erfcf,(_FLOAT_ARG x));
#endif
double _EXFUN(_erf_r,(struct _reent *, double x));
double _EXFUN(_erfc_r,(struct _reent *, double x));
_FLOAT_RET _EXFUN(_erff_r,(struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_erfcf_r,(struct _reent *, _FLOAT_ARG x));

#ifndef _REENT_ONLY
double _EXFUN(y0, (double x));
double _EXFUN(y1, (double x));
double _EXFUN(yn, (int n, double x));
double _EXFUN(j0, (double x));
double _EXFUN(j1, (double x));
double _EXFUN(jn, (int n, double x));
#endif
double _EXFUN(_y0_r, (struct _reent *, double x));
double _EXFUN(_y1_r, (struct _reent *, double x));
double _EXFUN(_yn_r, (struct _reent *, int n, double x));
double _EXFUN(_j0_r, (struct _reent *, double x));
double _EXFUN(_j1_r, (struct _reent *, double x));
double _EXFUN(_jn_r, (struct _reent *, int n, double x));

#ifndef _REENT_ONLY
_FLOAT_RET _EXFUN(y0f, (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(y1f, (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(ynf, (int n, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(j0f, (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(j1f, (_FLOAT_ARG x));
_FLOAT_RET _EXFUN(jnf, (int n, _FLOAT_ARG x));
#endif
_FLOAT_RET _EXFUN(_y0f_r, (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_y1f_r, (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_ynf_r, (struct _reent *, int n, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_j0f_r, (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_j1f_r, (struct _reent *, _FLOAT_ARG x));
_FLOAT_RET _EXFUN(_jnf_r, (struct _reent *, int n, _FLOAT_ARG x));

#ifndef _REENT_ONLY
double _EXFUN(hypot,(double,double));
_FLOAT_RET _EXFUN(hypotf,(_FLOAT_ARG, _FLOAT_ARG));
#endif
double _EXFUN(_hypot_r,(struct _reent *, double,double));
_FLOAT_RET _EXFUN(_hypotf_r,(struct _reent *, _FLOAT_ARG, _FLOAT_ARG));

double _EXFUN(infinity,(void));
_FLOAT_RET _EXFUN(infinityf,(void));

double _EXFUN(nan,(void));
_FLOAT_RET _EXFUN(nanf,(void));

struct exception 
{
  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
  int err;
};

int _EXFUN(matherr,(struct exception *e));

#define DOMAIN 1
#define SING 2
#define OVERFLOW 3
#define UNDERFLOW 4
#define TLOSS 5
#define PLOSS 6

#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		0.69314718055994530942
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_TWOPI         (M_PI * 2.0)
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_3PI_4		2.3561944901923448370E0
#define M_SQRTPI        1.77245385090551602792981
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440
#define M_LN2LO         1.9082149292705877000E-10
#define M_LN2HI         6.9314718036912381649E-1
#define M_SQRT3   	1.73205080756887719000
#define M_IVLN10        0.43429448190325182765 /* 1 / log(10) */
#define M_LOG2_E        0.693147180559945309417
#define M_INVLN2        1.4426950408889633870E0  /* 1 / log(2) */


#ifdef _SINGLE_PREC
#undef HUGE_VAL
#ifndef HUGE_VAL
#define HUGE_VAL 	3.40282347E+38
#endif
#define double  float
#define acos	acosf
#define _acos_r	_acosf_r
#define asin	asinf
#define _asin_r	_asinf_r
#define atan	atanf
#define atan2   atan2f
#define cos	cosf
#define _cos_r	_cosf_r
#define sin	sinf
#define _sinf_r	_sinf_r
#define tanf	tanf
#define _tanf_r	_tanf_r
#define cosh	coshf
#define _cosh_r	_coshf_r
#define sinh	sinhf
#define _sinh_r	_sinhf_r
#define tanh	tanhf
#define _tanh_r	_tanhf_r
#define exp	expf
#define _exp_r	_expf_r
#define frexp   frexpf
#define _frexp_r _frexpf_r
#define ldexp   ldexpf
#define _ldexp_r	_ldexpf_r
#define log	logf
#define _log_r	_logf_r
#define log10	log10f
#define _log10_r	_log10f_r
#define log2	log2f
#define _log2_r	_log2f_r
#define modf    modff
#define pow     powf
#define _pow_r	_powf_r
#define sqrt	sqrtf
#define _sqrt_r	_sqrtf_r
#define cbrt	cbrtf
#define _cbrt_r	_cbrtf_r
#define ceil	ceilf
#define fabs	fabsf
#define floor	floorf
#define fmod	fmodf
#define _fmod_r	_fmodf_r
#define asinh	asinhf
#define _asinh_r	_asinhf_r
#define acosh	acoshf
#define _acosh_r	_acoshf_r
#define atanh	atanhf
#define _atanh_r	_atanhf_r
#endif

#endif /* _STRICT_ANSI */

#ifdef __cplusplus
}
#endif
#endif /* _MATH_H_ */
