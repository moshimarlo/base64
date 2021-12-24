#ifndef __BASE_H_
#define __BASE_H_

#define COMPILE_TESTS

#include <stdint.h>

// Unit tests
#ifdef COMPILE_TESTS
int test_chars_to_4base(void);
int test_hex_to_base(void);
#endif

#endif // __BASE_H_
