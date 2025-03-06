/* cstr.h - v0.1 - public domain data structures - nickscha 2025

A C89 standard compliant, single header, nostdlib (no C Standard Library) String library.

USAGE
    // Use assert to break/stop program when expression is not met
    assert(1 == 1);

    // Use test as an conditional expression. If it fails it will log out the result but the program will continue
    test(10 % 5 == 0);


LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#ifndef CSTR_H
#define CSTR_H

/* #############################################################################
 * # COMPILER SETTINGS
 * #############################################################################
 */
/* Check if using C99 or later (inline is supported) */
#if __STDC_VERSION__ >= 199901L
#define CSTR_INLINE inline
#define CSTR_API extern
#elif defined(__GNUC__) || defined(__clang__)
#define CSTR_INLINE __inline__
#define CSTR_API static
#elif defined(_MSC_VER)
#define CSTR_INLINE __inline
#define CSTR_API static
#else
#define CSTR_INLINE
#define CSTR_API static
#endif

typedef unsigned char cstr_bool;

#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

typedef struct cstr
{
  char *data;
  long len;
} cstr;

typedef struct cstr_cut_marker
{
  cstr head;
  cstr tail;
  cstr_bool found;
} cstr_cut_marker;

CSTR_API CSTR_INLINE cstr cstr_init(char *s, long len)
{
  cstr result = {0};
  result.data = s;
  result.len = len;
  return (result);
}

#define CSTR(s) (cstr_init((s), sizeof(s) - 1))

CSTR_API CSTR_INLINE int cstr_memcmp(const void *s1, const void *s2, long n)
{
  const unsigned char *p1 = (const unsigned char *)s1;
  const unsigned char *p2 = (const unsigned char *)s2;

  while (n--)
  {
    if (*p1 != *p2)
    {
      return *p1 - *p2;
    }
    p1++;
    p2++;
  }
  return 0;
}

CSTR_API CSTR_INLINE cstr cstr_span(char *beg, char *end)
{
  cstr r = {0};
  r.data = beg;
  r.len = beg ? (long)(end - beg) : 0;
  return (r);
}

CSTR_API CSTR_INLINE cstr_bool cstr_equals(cstr a, cstr b)
{
  return (a.len == b.len && (!a.len || !cstr_memcmp(a.data, b.data, a.len)));
}

CSTR_API CSTR_INLINE cstr cstr_substring(cstr s, long i)
{
  if (i)
  {
    s.data += i;
    s.len -= i;
  }
  return (s);
}

CSTR_API CSTR_INLINE cstr cstr_trim_left(cstr s)
{
  for (; s.len && *s.data <= ' '; s.data++, --s.len)
  {
  }
  return (s);
}

CSTR_API CSTR_INLINE cstr cstr_trim_right(cstr s)
{
  for (; s.len && s.data[s.len - 1] <= ' '; --s.len)
  {
  }
  return (s);
}

CSTR_API CSTR_INLINE int cstr_index_of(cstr s, char c)
{
  long i;

  for (i = 0; i < s.len; ++i)
  {
    if (s.data[i] == c)
    {
      return (i);
    }
  }
  return (-1);
}

CSTR_API CSTR_INLINE int cstr_last_index_of(cstr s, char c)
{
  long i;

  for (i = s.len; i > 0; --i)
  {
    if (s.data[i] == c)
    {
      return (i);
    }
  }
  return (-1);
}

CSTR_API CSTR_INLINE cstr_cut_marker cstr_cut(cstr s, char c)
{
  cstr_cut_marker result = {0};

  char *beg;
  char *end;
  char *cut;

  if (!s.len)
  {
    return (result);
  }
  beg = s.data;
  end = s.data + s.len;
  cut = beg;
  for (; cut < end && *cut != c; cut++)
  {
  }
  result.found = cut < end;
  result.head = cstr_span(beg, cut);
  result.tail = cstr_span(cut + result.found, end);

  return (result);
}

CSTR_API CSTR_INLINE int cstr_parse_int(cstr s)
{
  int r = 0;
  int sign = 1;
  int i;

  for (i = 0; i < s.len; i++)
  {
    switch (s.data[i])
    {
    case '+':
      break;
    case '-':
      sign = -1;
      break;
    default:
      r = 10 * r + s.data[i] - '0';
    }
  }
  return (r * sign);
}

CSTR_API CSTR_INLINE float cstr_expt10(int e)
{
  float y = 1.0f;
  float x = e < 0 ? 0.1f : e > 0 ? 10.0f
                                 : 1.0f;
  int n = e < 0 ? e : -e;
  for (; n < -1; n /= 2)
  {
    y *= n % 2 ? x : 1.0f;
    x *= x;
  }
  return (x * y);
}

CSTR_API CSTR_INLINE float cstr_parse_float(cstr s)
{
  long i;
  float r = 0.0f;
  float sign = 1.0f;
  float exp = 0.0f;
  for (i = 0; i < s.len; i++)
  {
    switch (s.data[i])
    {
    case '+':
      break;
    case 'f':
      break;
    case '-':
      sign = -1;
      break;
    case '.':
      exp = 1;
      break;
    case 'E':
    case 'e':
      exp = ((cstr_bool)exp) ? exp : 1.0f;
      exp *= cstr_expt10(cstr_parse_int(cstr_substring(s, i + 1)));
      i = s.len;
      break;
    default:
      r = 10.0f * r + (s.data[i] - '0');
      exp *= 0.1f;
    }
  }
  return (sign * r * (((cstr_bool)exp) ? exp : 1.0f));
}

#endif /* CSTR_H */

/*
   ------------------------------------------------------------------------------
   This software is available under 2 licenses -- choose whichever you prefer.
   ------------------------------------------------------------------------------
   ALTERNATIVE A - MIT License
   Copyright (c) 2025 nickscha
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   ------------------------------------------------------------------------------
   ALTERNATIVE B - Public Domain (www.unlicense.org)
   This is free and unencumbered software released into the public domain.
   Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
   software, either in source code form or as a compiled binary, for any purpose,
   commercial or non-commercial, and by any means.
   In jurisdictions that recognize copyright laws, the author or authors of this
   software dedicate any and all copyright interest in the software to the public
   domain. We make this dedication for the benefit of the public at large and to
   the detriment of our heirs and successors. We intend this dedication to be an
   overt act of relinquishment in perpetuity of all present and future rights to
   this software under copyright law.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   ------------------------------------------------------------------------------
*/
