// Main header for the -*- C++ -*- complex number classes.
// This file is part of the GNU ANSI C++ Library.

#ifndef __COMPLEX__
#define __COMPLEX__

#include <std/complext.h>

#define __STD_COMPLEX

// ANSI complex types
typedef __complex<float> float_complex;
typedef __complex<double> double_complex;
typedef __complex<long double> long_double_complex;

// For backward compatibility
#ifndef __STRICT_ANSI__
typedef double_complex Complex;
typedef double_complex complex;
#endif

#endif
