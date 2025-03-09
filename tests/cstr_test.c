/* cstr.h - v0.1 - public domain data structures - nickscha 2025

A C89 standard compliant, single header, nostdlib (no C Standard Library) String library.

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#include "../cstr.h"
#include "test.h" /* Simple testing framework */

void cstr_test_basic_functions(void)
{
  cstr t1 = CSTR("this is a test\n");
  cstr t2 = CSTR("this is a test\n");
  cstr t3 = CSTR("another test  \n");
  cstr t4 = cstr_substring(t3, 8);
  cstr t5 = CSTR("  spaces  ");

  assert(t1.len == 15);
  assert(t2.len == 15);
  assert(t3.len == 15);
  assert(t5.len == 10);
  assert(cstr_equals(t1, t2));
  assert(!cstr_equals(t1, t3));
  assert(cstr_equals(t4, CSTR("test  \n")));
  assert(cstr_equals(cstr_trim_left(t5), CSTR("spaces  ")));
  assert(cstr_equals(cstr_trim_right(t5), CSTR("  spaces")));
  assert(cstr_equals(cstr_trim_left(cstr_trim_right(t5)), CSTR("spaces")));
  assert(cstr_equals(cstr_trim(t5), CSTR("spaces")));
  assert(cstr_index_of(t5, 's') == 2);
  assert(cstr_last_index_of(t5, 's') == 7);
  assert(cstr_index_of_substring(t1, CSTR("is")) == 2);
  assert(cstr_index_of_substring(t1, CSTR("z")) == -1);
}

void cstr_test_cut(void)
{
  cstr_cut_marker c = {0};
  char separator = '_';
  c.tail = CSTR("split_it_now");

  c = cstr_cut(c.tail, separator);
  assert(cstr_equals(c.head, cstr_init("split_it_now", c.head.len)));
  assert(cstr_equals(c.head, CSTR("split")));
  assert(c.found);

  c = cstr_cut(c.tail, separator);
  assert(cstr_equals(c.head, cstr_init("it_now", c.head.len)));
  assert(cstr_equals(c.head, CSTR("it")));
  assert(c.found);

  c = cstr_cut(c.tail, separator);
  assert(cstr_equals(c.head, cstr_init("now", c.head.len)));
  assert(cstr_equals(c.head, CSTR("now")));
  assert(!c.found);
}

void cstr_test_cut_print(void)
{
  char separator = '_';
  int i;
  cstr line;

  cstr_cut_marker c = {0};
  c.tail = CSTR("split_it_now");

  while (c.tail.len)
  {
    c = cstr_cut(c.tail, separator);
    line = c.head;
    for (i = 0; i < line.len; ++i)
    {
      TEST_FUNCTION_PRINTF("%c", line.data[i]);
    }
    TEST_FUNCTION_PRINTF("%s", "\n");
  }
}

#define CSTR_TEST_FABS(x) (((float)x < 0.0f) ? (float)-x : (float)x)
#define CSTR_TEST_FLOAT_EPS 0.00001f
#define CSTR_TEST_FLOAT_COMPARISION(a, b) (CSTR_TEST_FABS((float)(a - b)) < CSTR_TEST_FLOAT_EPS)

void cstr_test_parsing(void)
{
  cstr i1 = CSTR("123456");
  int r1 = cstr_parse_int(i1);

  cstr i2 = CSTR("-123456");
  int r2 = cstr_parse_int(i2);

  cstr h1 = CSTR("1A3F");

  assert(CSTR_TEST_FLOAT_COMPARISION(r1, 123456));
  assert(CSTR_TEST_FLOAT_COMPARISION(r2, -123456));
  assert(cstr_parse_bool(CSTR("1")) == true);
  assert(cstr_parse_bool(CSTR("true")) == true);
  assert(cstr_parse_bool(CSTR("0")) == false);
  assert(cstr_parse_bool(CSTR("false")) == false);
  assert(cstr_parse_hex(h1) == 6719);
}

void cstr_test_advanced(void)
{
  cstr s1 = CSTR("test");
  cstr s2 = CSTR("this is a long sequence and is a string");
  cstr s3 = CSTR("\"this string has quotes\"");
  cstr s4 = CSTR("\'abc\'");
  assert(cstr_starts_with(s1, CSTR("te")));
  assert(cstr_ends_with(s1, CSTR("st")));
  assert(cstr_count_char(s1, 't') == 2);
  assert(cstr_count_char(s1, 's') == 1);
  assert(cstr_count_char(s1, ' ') == 0);
  assert(cstr_count_substring(s2, CSTR("is")) == 3);
  assert(cstr_is_numeric(s1) == false);
  assert(cstr_is_numeric(CSTR("421312")) == true);
  assert(cstr_is_alpha(s1) == true);
  assert(cstr_contains(s1, CSTR("test")) == true);
  assert(cstr_contains(s1, CSTR("es")) == true);
  assert(cstr_contains(s1, CSTR("t")) == true);
  assert(cstr_equals_ignore_case(s1, CSTR("test")) == true);
  assert(cstr_equals_ignore_case(s1, CSTR("TEST")) == true);
  assert(cstr_equals_ignore_case(s1, CSTR("tESt")) == true);
  assert(cstr_equals_ignore_case(s1, CSTR("test ")) == false);
  assert(cstr_equals(cstr_strip_quotes(s3), CSTR("this string has quotes")) == true);
  assert(cstr_equals(cstr_strip_quotes(s4), CSTR("abc")) == true);
  assert(cstr_hash(s1) == 3556498);
}

void cstr_test_data_manipulating_functions(void)
{
  char b1[] = "hello world";
  cstr s1 = cstr_init_mut(b1, sizeof(b1) - 1);

  cstr_reverse(s1);
  assert(cstr_equals(s1, CSTR("dlrow olleh")));
  cstr_to_uppercase(s1);
  assert(cstr_equals(s1, CSTR("DLROW OLLEH")));
  cstr_to_lowercase(s1);
  assert(cstr_equals(s1, CSTR("dlrow olleh")));
  cstr_reverse(s1);
  assert(cstr_equals(s1, CSTR("hello world")));
}

int main(void)
{

  cstr_test_basic_functions();
  cstr_test_cut();
  cstr_test_cut_print();
  cstr_test_parsing();
  cstr_test_advanced();
  cstr_test_data_manipulating_functions();

  return 0;
}

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
