// Main templates for the -*- C++ -*- string classes.
// Copyright (C) 1994, 1995 Free Software Foundation

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

// Written by Jason Merrill based upon the specification by Takanori Adachi
// in ANSI X3J16/94-0013R2.

#ifdef __GNUG__
#pragma interface
#endif

#include <std/stddef.h>
#include <std/straits.h>

#if _G_USE_EXCEPTIONS

#include <stdexcept>
#define OUTOFRANGE(cond) \
  do { if (!(cond)) throw out_of_range (#cond); } while (0)
#define LENGTHERROR(cond) \
  do { if (!(cond)) throw length_error (#cond); } while (0)

#else

#include <cassert>
#define OUTOFRANGE(cond) assert (!(cond))
#define LENGTHERROR(cond) assert (!(cond))

#endif

class istream; class ostream;

// Should be a nested class basic_string<charT, traits>::Rep, but nested
// classes don't work well with templates in g++.
template <class charT, class traits = string_char_traits<charT> >
struct __bsrep {
  typedef __bsrep Rep;

  size_t len, res;
  unsigned char ref;

  charT* data () { return (charT *)(this + 1); }
  charT& operator[] (size_t s) { return data () [s]; }
  Rep* grab () { ++ref; return this; }
  void release () { if (--ref == 0) delete this; }

  inline static void * operator new (size_t, size_t);
  inline static Rep* create (size_t);

  inline void copy (size_t, const charT *, size_t);
  inline void move (size_t, const charT *, size_t);
  inline void set  (size_t, const charT,   size_t);

#if _G_ALLOC_CONTROL
  // These function pointers allow you to modify the allocation policy used
  // by the string classes.  By default they expand by powers of two, but
  // this may be excessive for space-critical applications.

  // Returns true if ALLOCATED is too much larger than LENGTH
  static bool (*excess_slop) (size_t length, size_t allocated);
  inline static bool default_excess (size_t, size_t);

  // Returns a good amount of space to allocate for a string of length LENGTH
  static size_t (*frob_size) (size_t length);
  inline static size_t default_frob (size_t);
#else
  inline static bool excess_slop (size_t, size_t);
  inline static size_t frob_size (size_t);
#endif

private:
  Rep &operator= (const Rep &);
};

// #include <iterator.h>

template <class charT, class traits = string_char_traits<charT> >
class basic_string {
public:
  typedef charT char_type;
  typedef traits traits_type;
  typedef __bsrep<charT, traits> Rep;

  const charT* data () const
    { return rep->data(); }
  size_t length () const
    { return rep->len; }
  size_t reserve () const
    { return rep->res; }

  basic_string& operator= (const basic_string& str)
    { str.rep->grab (); rep->release (); rep = str.rep; return *this; }

  basic_string (): rep (nilRep.grab ()) { }
  basic_string (const basic_string& str): rep (str.rep->grab ()) { }
  basic_string (size_t size, capacity cap);
  basic_string (const basic_string& str, size_t pos, size_t n = NPOS)
    : rep (nilRep.grab ()) { assign (str, pos, n); }
  basic_string (const charT* s, size_t n)
    : rep (nilRep.grab ()) { assign (s, n); }
  basic_string (const charT* s)
    : rep (nilRep.grab ()) { assign (s); }
  explicit basic_string (charT c, size_t n = 1)
    : rep (nilRep.grab ()) { assign (c, n); }

  ~basic_string ()
    { rep->release (); }

  basic_string& append (const basic_string& str, size_t pos = 0,
			size_t n = NPOS)
    { return replace (length (), 0, str, pos, n); }
  basic_string& append (const charT* s, size_t n)
    { return replace (length (), 0, s, n); }
  basic_string& append (const charT* s)
    { return append (s, traits::length (s)); }
  basic_string& append (charT c, size_t n = 1)
    { return replace (length (), 0, c, n); }

  basic_string& assign (const basic_string& str, size_t pos = 0,
			size_t n = NPOS)
    { return replace (0, NPOS, str, pos, n); }
  basic_string& assign (const charT* s, size_t n)
    { return replace (0, NPOS, s, n); }
  basic_string& assign (const charT* s)
    { return assign (s, traits::length (s)); }
  basic_string& assign (charT c, size_t n = 1)
    { return replace (0, NPOS, c, n); }

  basic_string& operator= (const charT* s)
    { return assign (s); }
  basic_string& operator= (charT c)
    { return assign (c); }

  basic_string& operator+= (const basic_string& rhs)
    { return append (rhs); }
  basic_string& operator+= (const charT* s)
    { return append (s); }
  basic_string& operator+= (charT c)
    { return append (c); }

  basic_string& insert (size_t pos1, const basic_string& str,
			size_t pos2 = 0, size_t n = NPOS)
    { return replace (pos1, 0, str, pos2, NPOS); }
  basic_string& insert (size_t pos, const charT* s, size_t n)
    { return replace (pos, 0, s, n); }
  basic_string& insert (size_t pos, const charT* s)
    { return insert (pos, s, traits::length (s)); }
  basic_string& insert (size_t pos, charT c, size_t n = 1)
    { return replace (pos, 0, c, n); }

  basic_string& remove (size_t pos = 0, size_t n = NPOS)
    { return replace (pos, n, (const charT *)0, 0); }

  basic_string& replace (size_t pos1, size_t n1, const basic_string& str,
			 size_t pos2 = 0, size_t n2 = NPOS);
  basic_string& replace (size_t pos, size_t n1, const charT* s, size_t n2);
  basic_string& replace (size_t pos, size_t n1, const charT* s)
    { return replace (pos, n1, s, traits::length (s)); }
  basic_string& replace (size_t pos, size_t n, charT c, size_t n = 1);

  charT operator[] (size_t pos) const
    {
      if (pos == length ())
	return eos ();
      return data ()[pos];
    }
private:
  void unique () { if (rep->ref > 1) alloc (reserve (), true); }

public:
  charT& operator[] (size_t pos)
    { unique (); return (*rep)[pos]; }

  charT get_at (size_t pos) const
    {
      OUTOFRANGE (pos >= length ());
      return data ()[pos];
    }
  void put_at (size_t pos, charT c)
    {
      OUTOFRANGE (pos > length ());
      if (pos == length ())
	append (c);
      else
	(*this)[pos] = c;
    }
private:
  static charT eos () { return traits::eos (); }
  void terminate () const
    {
      if (reserve () < length () + 1)
	alloc (length () + 1, true);
      traits::assign ((*rep)[length ()], eos ());
    }

public:
  const charT* c_str () const
    { terminate (); return data (); }
  void resize (size_t n, charT c);
  void resize (size_t n)
    { resize (n, eos ()); }
  void reserve (size_t s) { }

  size_t copy (charT* s, size_t n, size_t pos = 0);

  size_t find (const basic_string& str, size_t pos = 0) const
    { return find (str.data(), pos, str.length()); }
  size_t find (const charT* s, size_t pos, size_t n) const;
  size_t find (const charT* s, size_t pos = 0) const
    { return find (s, pos, traits::length (s)); }
  size_t find (charT c, size_t pos = 0) const;

  size_t rfind (const basic_string& str, size_t pos = NPOS) const
    { return rfind (str.data(), pos, str.length()); }
  size_t rfind (const charT* s, size_t pos, size_t n) const;
  size_t rfind (const charT* s, size_t pos = NPOS) const
    { return rfind (s, pos, traits::length (s)); }
  size_t rfind (charT c, size_t pos = NPOS) const;

  size_t find_first_of (const basic_string& str, size_t pos = 0) const
    { return find_first_of (str.data(), pos, str.length()); }
  size_t find_first_of (const charT* s, size_t pos, size_t n) const;
  size_t find_first_of (const charT* s, size_t pos = 0) const
    { return find_first_of (s, pos, traits::length (s)); }
  size_t find_first_of (charT c, size_t pos = 0) const
    { return find (c, pos); }

  size_t find_last_of (const basic_string& str, size_t pos = NPOS) const
    { return find_last_of (str.data(), pos, str.length()); }
  size_t find_last_of (const charT* s, size_t pos, size_t n) const;
  size_t find_last_of (const charT* s, size_t pos = NPOS) const
    { return find_last_of (s, pos, traits::length (s)); }
  size_t find_last_of (charT c, size_t pos = NPOS) const
    { return rfind (c, pos); }

  size_t find_first_not_of (const basic_string& str, size_t pos = 0) const
    { return find_first_not_of (str.data(), pos, str.length()); }
  size_t find_first_not_of (const charT* s, size_t pos, size_t n) const;
  size_t find_first_not_of (const charT* s, size_t pos = 0) const
    { return find_first_not_of (s, pos, traits::length (s)); }
  size_t find_first_not_of (charT c, size_t pos = 0) const;

  size_t find_last_not_of (const basic_string& str, size_t pos = NPOS) const
    { return find_last_not_of (str.data(), pos, str.length()); }
  size_t find_last_not_of (const charT* s, size_t pos, size_t n) const;
  size_t find_last_not_of (const charT* s, size_t pos = NPOS) const
    { return find_last_not_of (s, pos, traits::length (s)); }
  size_t find_last_not_of (charT c, size_t pos = NPOS) const;

  basic_string substr (size_t pos = 0, size_t n = NPOS) const
    { return basic_string (*this, pos, n); }

  int compare (const basic_string& str, size_t pos = 0, size_t n = NPOS) const;
  // There is no 'strncmp' equivalent for charT pointers.
  int compare (const charT* s, size_t pos, size_t n) const;
  int compare (const charT* s, size_t pos = 0) const
    { return compare (s, pos, traits::length (s)); }
  int compare (charT c, size_t pos = 0, size_t n = 1) const;

  friend istream &operator>> (istream &, basic_string &);

  // STL interface section

  typedef charT value_type;
  typedef charT* pointer;
  typedef charT& reference;
  typedef const charT& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  class iterator /*: public bidirectional_iterator <charT, ptrdiff_t>*/ {
    friend class basic_string;
    basic_string *str;
    size_t pos;
  protected:
    iterator (basic_string *s, size_t p) : str (s), pos (p) { }
  public:
    bool operator== (const iterator& y) const
      { return str == y.str && pos == y.pos; }
    bool operator!= (const iterator& y) const { return !operator== (y); }
    charT& operator* () const { return (*str)[pos]; }
    iterator& operator++ () { ++pos; return *this; }
    iterator operator++ (int) { iterator tmp = *this; ++*this; return tmp; }
    iterator& operator-- () { --pos; return *this; }
    iterator operator-- (int) { iterator tmp = *this; --*this; return tmp; }
  };

  iterator begin () { return iterator (this, 0); }
  iterator end () { return iterator (this, length ()); }

  class const_iterator /*: public bidirectional_iterator <charT, ptrdiff_t>*/ {
    friend class basic_string;
    const basic_string *str;
    size_t pos;
  protected:
    const_iterator (const basic_string *s, size_t p) : str (s), pos (p) { }
  public:
    bool operator== (const const_iterator& y) const
      { return str == y.str && pos == y.pos; }
    bool operator!= (const const_iterator& y) const { return !operator== (y); }
    charT operator* () const { return (*str)[pos]; }
    const_iterator& operator++ () { ++pos; return *this; }
    const_iterator operator++ (int)
      { const_iterator tmp = *this; ++*this; return tmp; }
    const_iterator& operator-- () { --pos; return *this; }
    const_iterator operator-- (int)
      { const_iterator tmp = *this; --*this; return tmp; }
  };

  const_iterator begin () const { return const_iterator (this, 0); }
  const_iterator end () const { return const_iterator (this, length ()); }

private:
  void alloc (size_t size, bool save) const;
  static size_t _find (const charT* ptr, charT c, size_t xpos, size_t len);
  inline bool check_realloc (size_t s) const;

  static Rep nilRep;
  Rep *rep;
};

template <class charT, class traits>
inline basic_string <charT, traits>
operator+ (const basic_string <charT, traits>& lhs,
	   const basic_string <charT, traits>& rhs)
{
  basic_string <charT, traits> str (lhs);
  str.append (rhs);
  return str;
}

template <class charT, class traits>
inline basic_string <charT, traits>
operator+ (const charT* lhs, const basic_string <charT, traits>& rhs)
{
  basic_string <charT, traits> str (lhs);
  str.append (rhs);
  return str;
}

template <class charT, class traits>
inline basic_string <charT, traits>
operator+ (charT lhs, const basic_string <charT, traits>& rhs)
{
  basic_string <charT, traits> str (lhs);
  str.append (rhs);
  return str;
}

template <class charT, class traits>
inline basic_string <charT, traits>
operator+ (const basic_string <charT, traits>& lhs, const charT* rhs)
{
  basic_string <charT, traits> str (lhs);
  str.append (rhs);
  return str;
}

template <class charT, class traits>
inline basic_string <charT, traits>
operator+ (const basic_string <charT, traits>& lhs, charT rhs)
{
  basic_string <charT, traits> str (lhs);
  str.append (rhs);
  return str;
}

template <class charT, class traits>
inline bool
operator== (const basic_string <charT, traits>& lhs,
	    const basic_string <charT, traits>& rhs)
{
  return (lhs.compare (rhs) == 0);
}

template <class charT, class traits>
inline bool
operator== (const charT* lhs, const basic_string <charT, traits>& rhs)
{
  return (rhs.compare (lhs) == 0);
}

template <class charT, class traits>
inline bool
operator== (charT lhs, const basic_string <charT, traits>& rhs)
{
  return (rhs.compare (lhs) == 0);
}

template <class charT, class traits>
inline bool
operator== (const basic_string <charT, traits>& lhs, const charT* rhs)
{
  return (lhs.compare (rhs) == 0);
}

template <class charT, class traits>
inline bool
operator== (const basic_string <charT, traits>& lhs, charT rhs)
{
  return (lhs.compare (rhs) == 0);
}

template <class charT, class traits>
inline bool
operator!= (const basic_string <charT, traits>& lhs,
	    const basic_string <charT, traits>& rhs)
{
  return (lhs.compare (rhs) != 0);
}

template <class charT, class traits>
inline bool
operator!= (const charT* lhs, const basic_string <charT, traits>& rhs)
{
  return (rhs.compare (lhs) != 0);
}

template <class charT, class traits>
inline bool
operator!= (charT lhs, const basic_string <charT, traits>& rhs)
{
  return (rhs.compare (lhs) != 0);
}

template <class charT, class traits>
inline bool
operator!= (const basic_string <charT, traits>& lhs, const charT* rhs)
{
  return (lhs.compare (rhs) != 0);
}

template <class charT, class traits>
inline bool
operator!= (const basic_string <charT, traits>& lhs, charT rhs)
{
  return (lhs.compare (rhs) != 0);
}

class istream; class ostream;
template <class charT, class traits> istream&
operator>> (istream&, basic_string <charT, traits>&);
template <class charT, class traits> ostream&
operator<< (ostream&, basic_string <charT, traits>);

#if !defined (_G_NO_EXTERN_TEMPLATES)
#include <std/sinst.h>
#endif
