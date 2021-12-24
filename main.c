#include "base.h"
#include <stdio.h>

int run_tests(void)
{
	int success = 0;
	success += test_chars_to_4base();
	success += test_hex_to_base();
	return success;
}

int main(void)
{
	run_tests();
}

