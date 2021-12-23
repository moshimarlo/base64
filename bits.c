#include "bits.h"
#include <stdio.h>

// Print bits for debugging
// From https://en.wikipedia.org/wiki/Bitwise_operations_in_C
void show_bits(unsigned int x)
{
    int i = 0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}
