// Member templates for the -*- C++ -*- complex number classes.
// Copyright (C) 1994 Free Software Foundation

// This file is part of the GNU ANSI C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with GNU CC; see the file COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

// As a special exception, if you link this library with files
// compiled with a GNU compiler to produce an executable, this does not cause
// the resulting executable to be covered by the GNU General Public License.
// This exception does not however invalidate any other reasons why
// the executable file might be covered by the GNU General Public License.

// Written by Jason Merrill based upon the specification in the 27 May 1994
// C++ working paper, ANSI document X3J16/94-0098.

#include <std/complex.h>

template <class FLOAT> __complex<FLOAT>
operator / (FLOAT x, __complex<FLOAT> y)
{
  FLOAT d = norm (y);
  return __complex<FLOAT> ((x * real (y)) / d, (- x * imag (y)) / d);
}

template <class FLOAT> __complex<FLOAT>
cos (__complex<FLOAT> x)
{
  return __complex<FLOAT> (cos (real (x)) * cosh (imag (x)),
			   - sin (real (x)) * sinh (imag (x)));
}

template <class FLOAT> __complex<FLOAT>
cosh (__complex<FLOAT> x)
{
  return __complex<FLOAT> (cosh (real (x)) * cos (imag (x)),
			   sinh (real (x)) * sin (imag (x)));
}

template <class FLOAT> __complex<FLOAT>
exp (__complex<FLOAT> x)
{
  return polar (FLOAT (exp (real (x))), imag (x));
}

template <class FLOAT> __complex<FLOAT>
log (__complex<FLOAT> x)
{
  return __complex<FLOAT> (log (abs (x)), arg (x));
}

template <class FLOAT> __complex<FLOAT>
pow (__complex<FLOAT> x, __complex<FLOAT> y)
{
  FLOAT logr = log (abs (x));
  FLOAT t = arg (x);

  return polar (FLOAT (exp (logr * real (y) - imag (y) * t)),
		FLOAT (imag (y) * logr + real (y) * t));
}

template <class FLOAT> __complex<FLOAT>
pow (__complex<FLOAT> x, FLOAT y)
{
  return exp (FLOAT (y) * log (x));
}

template <class FLOAT> __complex<FLOAT>
pow (FLOAT x, __complex<FLOAT> y)
{
  return exp (y * FLOAT (log (x)));
}

template <class FLOAT> __complex<FLOAT>
sin (__complex<FLOAT> x)
{
  return __complex<FLOAT> (sin (real (x)) * cosh (imag (x)),
			   cos (real (x)) * sinh (imag (x)));
}

template <class FLOAT> __complex<FLOAT>
sinh (__complex<FLOAT> x)
{
  return __complex<FLOAT> (sinh (real (x)) * cos (imag (x)),
			   cosh (real (x)) * sin (imag (x)));
}

#include <iostream.h>

template <class FLOAT> istream&
operator >> (istream& is, __complex<FLOAT>& x)
{
  char ch;
  FLOAT re, im;

  if (is >> ch && ch == '('
      && is >> re >> ch && ch == ','
      && is >> im >> ch && ch == ')')
    x = __complex<FLOAT> (re, im);

  return is;
}

template <class FLOAT> ostream&
operator << (ostream& os, __complex<FLOAT> x)
{
  return os << '(' << real (x) << ',' << imag (x) << ')';
}

// The code below is adapted from f2c's libF77, and is subject to this
// copyright:

/****************************************************************
Copyright 1990, 1991, 1992, 1993 by AT&T Bell Laboratories and Bellcore.

Permission to use, copy, modify, and distribute this software
and its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that the copyright notice and this
permission notice and warranty disclaimer appear in supporting
documentation, and that the names of AT&T Bell Laboratories or
Bellcore or any of their entities not be used in advertising or
publicity pertaining to distribution of the software without
specific, written prior permission.

AT&T and Bellcore disclaim all warranties with regard to this
software, including all implied warranties of merchantability
and fitness.  In no event shall AT&T or Bellcore be liable for
any special, indirect or consequential damages or any damages
whatsoever resulting from loss of use, data or profits, whether
in an action of contract, negligence or other tortious action,
arising out of or in connection with the use or performance of
this software.
****************************************************************/

template <class FLOAT> __complex<FLOAT>& __complex<FLOAT>::
operator /= (__complex y)
{
  FLOAT ar = fabs (y.re);
  FLOAT ai = fabs (y.im);
  FLOAT nr, ni;
  FLOAT t, d;
  if (ar <= ai)
    {
      t = y.re / y.im;
      d = y.im * (1 + t*t);
      nr = (re * t + im) / d;
      ni = (im * t - re) / d;
    }
  else
    {
      t = y.im / y.re;
      d = y.re * (1 + t*t);
      nr = (re + im * t) / d;
      ni = (im - re * t) / d;
    }
  re = nr;
  im = ni;
  return *this;
}

template <class FLOAT> __complex<FLOAT>
operator / (__complex<FLOAT> x, __complex<FLOAT> y)
{
  FLOAT ar = fabs (real (y));
  FLOAT ai = fabs (imag (y));
  FLOAT nr, ni;
  FLOAT t, d;
  if (ar <= ai)
    {
      t = real (y) / imag (y);
      d = imag (y) * (1 + t*t);
      nr = (real (x) * t + imag (x)) / d;
      ni = (imag (x) * t - real (x)) / d;
    }
  else
    {
      t = imag (y) / real (y);
      d = real (y) * (1 + t*t);
      nr = (real (x) + imag (x) * t) / d;
      ni = (imag (x) - real (x) * t) / d;
    }
  return __complex<FLOAT> (nr, ni);
}

template <class FLOAT> __complex<FLOAT>
pow (__complex<FLOAT> x, int y)
{
  if (y == 0)
    return __complex<FLOAT> (1.0);
  __complex<FLOAT> r (1.0);
  if (y < 0)
    {
      y = -y;
      x = 1/x;
    }
  for (;;)
    {
      if (y & 1)
	r *= x;
      if (y >>= 1)
	x *= x;
      else
	return r;
    }
}

template <class FLOAT> __complex<FLOAT>
sqrt (__complex<FLOAT> x)
{
  FLOAT r = abs (x);
  FLOAT nr, ni;
  if (r == 0.0)
    nr = ni = r;
  else if (real (x) > 0)
    {
      nr = sqrt (0.5 * (r + real (x)));
      ni = imag (x) / nr / 2;
    }
  else
    {
      ni = sqrt (0.5 * (r - real (x)));
      if (imag (x) < 0)
	ni = - ni;
      nr = imag (x) / ni / 2;
    }
  return __complex<FLOAT> (nr, ni); 
}
