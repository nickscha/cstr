# cstr
A C89 standard compliant, single header, nostdlib (no C Standard Library) string library.

For more information please look at the "cstr.h" file or take a look at the "examples" or "tests" folder.

## Quick Start

Download or clone cstr.h and include it in your project.

```C
#include "cstr.h"

int main() {

    /* Mutable String */
    cstr t1 = CSTR("  spaces  ");
    if(!cstr_equals(cstr_trim(t1), CSTR("spaces"))) {
      /* ... */
    }

    /* Immutable String functions */
    char b1[] = "hello world";
    cstr s1 = cstr_init(b1, sizeof(b1) - 1);
    cstr_reverse(s1);      /* "dlrow olleh" */
    cstr_to_uppercase(s1); /* "DLROW OLLEH" */
    cstr_to_lowercase(s1); /* "dlrow olleh" */

    return 0;
}
```

## Run Example: nostdlib, freestsanding

In this repo you will find the "examples/cstr_win32_nostdlib.c" with the corresponding "build.bat" file which
creates an executable only linked to "kernel32" and "user32" and is not using the C standard library and executes the program afterwards.

## "nostdlib" Motivation & Purpose

nostdlib is a lightweight, minimalistic approach to C development that removes dependencies on the standard library. The motivation behind this project is to provide developers with greater control over their code by eliminating unnecessary overhead, reducing binary size, and enabling deployment in resource-constrained environments.

Many modern development environments rely heavily on the standard library, which, while convenient, introduces unnecessary bloat, security risks, and unpredictable dependencies. nostdlib aims to give developers fine-grained control over memory management, execution flow, and system calls by working directly with the underlying platform.

### Benefits

#### Minimal overhead
By removing the standard library, nostdlib significantly reduces runtime overhead, allowing for faster execution and smaller binary sizes.

#### Increased security
Standard libraries often include unnecessary functions that increase the attack surface of an application. nostdlib mitigates security risks by removing unused and potentially vulnerable components.

#### Reduced binary size
Without linking to the standard library, binaries are smaller, making them ideal for embedded systems, bootloaders, and operating systems where storage is limited.

#### Enhanced performance
Direct control over system calls and memory management leads to performance gains by eliminating abstraction layers imposed by standard libraries.

#### Better portability
By relying only on fundamental system interfaces, nostdlib allows for easier porting across different platforms without worrying about standard library availability.

## cstr Library Documentation

This header file defines a set of functions and types for manipulating C-style strings (null-terminated character arrays) in a more structured and safer manner. It provides utilities for string comparison, substring extraction, case manipulation, numeric parsing, and various other operations.

### Types

- `cstr_bool`: A boolean type (0 or 1) used for flagging true or false values.
- `cstr`: A structure that represents a string. It contains:
  - `data`: A pointer to the character data.
  - `len`: The length of the string.
- `cstr_cut_marker`: A structure used to represent a substring split at a marker (character), containing:
  - `head`: The part before the marker.
  - `tail`: The part after the marker.
  - `found`: A boolean flag indicating whether the marker was found.

### Functions

#### Initialization and Creation

- **`cstr cstr_init(char *s, long len)`**: Initializes a `cstr` with the given string `s` and length `len`.
- **`#define CSTR(s)`**: Macro that initializes a `cstr` with the string `s` and automatically calculates its length.

#### Comparison Functions

- **`int cstr_memcmp(const void *s1, const void *s2, long n)`**: Compares two memory blocks byte by byte for `n` bytes.
- **`cstr_bool cstr_equals(cstr a, cstr b)`**: Checks if two `cstr` objects are equal in both length and content.
- **`cstr_bool cstr_equals_ignore_case(cstr a, cstr b)`**: Compares two `cstr` objects case-insensitively.
  
#### Substring and Trimming

- **`cstr cstr_substring(cstr s, long i)`**: Returns a substring starting from index `i`.
- **`cstr cstr_trim_left(cstr s)`**: Trims whitespace characters from the left side of a string.
- **`cstr cstr_trim_right(cstr s)`**: Trims whitespace characters from the right side of a string.
- **`cstr cstr_trim(cstr s)`**: Trims whitespace characters from both sides of the string.

#### String Search Functions

- **`cstr_bool cstr_starts_with(cstr s, cstr prefix)`**: Checks if the string starts with the given prefix.
- **`cstr_bool cstr_ends_with(cstr s, cstr suffix)`**: Checks if the string ends with the given suffix.
- **`cstr_bool cstr_contains(cstr s, cstr sub)`**: Checks if the string contains the given substring.

#### Counting Functions

- **`long cstr_count_char(cstr s, char c)`**: Counts the occurrences of a character `c` in the string `s`.
- **`long cstr_count_substring(cstr s, cstr sub)`**: Counts how many times a substring appears in the string `s`.

#### Type Checking

- **`cstr_bool cstr_is_numeric(cstr s)`**: Checks if the string represents a numeric value (only digits).
- **`cstr_bool cstr_is_alpha(cstr s)`**: Checks if the string contains alphabetic characters (non-numeric).

#### Indexing Functions

- **`int cstr_index_of(cstr s, char c)`**: Returns the index of the first occurrence of the character `c` in the string `s`.
- **`int cstr_index_of_substring(cstr s, cstr sub)`**: Returns the index of the first occurrence of the substring `sub` in the string `s`.
- **`int cstr_last_index_of(cstr s, char c)`**: Returns the index of the last occurrence of the character `c` in the string `s`.

#### String Modifications

- **`cstr cstr_strip_quotes(cstr s)`**: Removes leading and trailing quotes (single or double) from the string.
- **`unsigned long cstr_hash(cstr s)`**: Computes a hash value for the string.
- **`cstr_cut_marker cstr_cut(cstr s, char c)`**: Splits the string into two parts (head and tail) at the first occurrence of the character `c`.

#### Parsing Functions

- **`cstr_bool cstr_parse_bool(cstr s)`**: Parses the string as a boolean (`"1"` or `"true"`).
- **`int cstr_parse_hex(cstr s)`**: Parses a hexadecimal string to an integer.
- **`int cstr_parse_int(cstr s)`**: Parses a string representing an integer value.
- **`float cstr_parse_float(cstr s)`**: Parses a string representing a floating-point number.

#### Mutable String Functions

- **`void cstr_reverse(cstr s)`**: Reverses the string in place.
- **`void cstr_to_uppercase(cstr s)`**: Converts the string to uppercase.
- **`void cstr_to_lowercase(cstr s)`**: Converts the string to lowercase.

### Notes

- The `cstr` structure is designed to hold a string and its length, providing a safer and more flexible way to handle C-style strings.
- All string manipulation functions work in a similar way: they operate on the `cstr` structure and return a new `cstr` (except for mutating functions like `cstr_reverse`).
- Functions like `cstr_equals`, `cstr_contains`, `cstr_index_of`, etc., allow for efficient string searching and comparison without relying on null-terminated strings directly.
  
This library helps improve the management of C strings by providing a range of utility functions for common string operations, while ensuring that string lengths are properly handled and avoiding the pitfalls of null-terminated string manipulations.
