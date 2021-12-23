#include "base.h"
#include <stdio.h>

int run_tests(void)
{
	int success = 0;
	success = test_chunk_to_24bs();
	return success;
}

int main(void)
{
	run_tests();
}

