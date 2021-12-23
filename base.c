#include "base.h"
#include "bits.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const uint8_t table[64] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

// Local functions
static char get_char(char x);
static char* chars_to_4base(char input[3]);


// Convert sextet to its base64 value
char get_char(char x)
{
	return (x < 64) ? table[(size_t) x] : '?';
}

char* chars_to_4base(char input[3])
{
	// Squash the three chars into 24 bits
	uint32_t chunk = input[0] << 16;
	chunk += input[1] << 8;
	chunk += input[2];

	printf("chunk:\n");
	show_bits(chunk);

	// TODO: free this
	char *ret = malloc(sizeof(char) * 5);

	// Convert each sextet into base64 character
	char first = chunk >> 18 & 0x3F;
	printf("first:\n");
	show_bits(first);
	char second = (chunk >> 12) & 0x3F;
	printf("second:\n");
	show_bits(second);
	char third = (chunk >> 6) & 0x3F;
	printf("third:\n");
	show_bits(third);
	char fourth = chunk & 0x3F;
	printf("fourth:\n");
	show_bits(fourth);

	ret[0] = get_char(first);
	ret[1] = get_char(second);
	ret[2] = get_char(third);
	ret[3] = get_char(fourth);

	return ret;
}

uint8_t hex_to_base(char *input)
{
	return 0;
}

// Unit tests
int test_chunk_to_24bs(void)
{
	char inp[3] = "Man";
	char* val = chars_to_4base(inp);
	val[4] = '\0';
	printf("%s\n", val);
	assert(!strcmp(val, "TWFu"));
	free(val);
	return 0;
}
