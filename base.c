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
static char get_char(char x)
{
	return (x < 64) ? table[(size_t) x] : '?';
}

/*
 * Convert three input chars to four Base64 chars
 */
char* chars_to_4base(char input[3])
{
	// Squash the three chars into 24 bits
	uint32_t chunk = input[0] << 16;
	chunk += input[1] << 8;
	chunk += input[2];

	/*printf("chunk:\n");*/
	/*show_bits(chunk);*/
	char *ret = malloc(sizeof(char) * 4);

	// Convert each sextet into base64 character
	char first = chunk >> 18 & 0x3F;
	/*printf("first:\n");*/
	/*show_bits(first);*/
	char second = (chunk >> 12) & 0x3F;
	/*printf("second:\n");*/
	/*show_bits(second);*/
	char third = (chunk >> 6) & 0x3F;
	/*printf("third:\n");*/
	/*show_bits(third);*/
	char fourth = chunk & 0x3F;
	/*printf("fourth:\n");*/
	/*show_bits(fourth);*/

	ret[0] = get_char(first);
	ret[1] = get_char(second);
	ret[2] = get_char(third);
	ret[3] = get_char(fourth);

	return ret;
}

char* hex_to_base(char *input, size_t n)
{
	char *ret = malloc(sizeof(char) * 16);
	size_t maxlen = 16;
	size_t ret_n = 0;
	for (size_t i = 0; i < n; i += 3) {
		char inp[3] = { input[i], input[i+1], input[i+2] };
		char *str = chars_to_4base(inp);

		if (ret_n + 4 > maxlen) ret = realloc(ret, sizeof(char) * (maxlen * 2)); 
		ret_n += 4;
		
		// append to return string
		for (int j = 0, k = i; j < 4; j++) {
			ret[k++] = str[j];
		}
		free(str);
	}
	//TODO: null-terminate the string if meant to be printed
	return ret;
}

// Unit tests
int test_chars_to_4base(void)
{
	char *test_name = "chars_to_4base";
	int success = 0;
	char inp[3] = "Man";
	char* val = chars_to_4base(inp);
	val[4] = '\0';
	printf("%s\n", val);
	switch (strcmp(val, "TWFu")) {
		case 0: {
			printf("Test: %s successful!", test_name);
			break;
		}
		default: {
			printf("Test: %s failed!", test_name);
			success = -1;
			break;
		}
	}
	free(val);
	return success;
}

int test_hex_to_base(void)
{
	char *inp = "Many hands make light work.";
	size_t n = strlen(inp);
	printf("length of input: %lu\n", n);
	char *out = hex_to_base(inp, n);
	//strcat(out, '\0');
	snprintf(out, 16, "s");
	free(out);
	return 0;
}
