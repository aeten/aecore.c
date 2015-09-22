#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define AETEN_CORE__VERBOSE 1
#define AETEN_CORE__IS_VERBOSE(flags) ((flags & AETEN_CORE__VERBOSE)? 1: 0)

typedef struct s_aeten_core_collections__map_entry {
	const void *key;
	const void *value;
} aeten_core_collections__map_entry_t;

//struct s_aeten_core_collections__map {
//	aeten_core_collections__map_entry_t *entries;
//	size_t size;
//} aeten_core_collections__map_t;

//void aeten_core_collections__map(const aeten_core_collections__map_entry_t *pattern_map) {
//}

void aeten_core__to_lower_case(char *str) {
	for(;*str;++str) {
		if ((*str > 0x40) && (*str<0x5b)) {
			*str = (*str|0x60);
		}
	}
}

int aeten_core__is_opt(const char *pattern, const char *opt) {
	char pattern_copy[strlen(pattern)+1];
	strcpy(pattern_copy, pattern);

	char* token = NULL;
	while ((token = strtok(((token == NULL) ? pattern_copy: 0), "|")) != NULL) {
		if (0 == strcmp(token, opt)) {
			return 0;
		}
	}
	return 1;
}

int aeten_core__opt(const aeten_core_collections__map_entry_t *pattern_map, size_t size, const char *opt) {
	int i;
	for(i=0;i<size; ++i, ++pattern_map) {
		if (0==aeten_core__is_opt((char *)(*pattern_map).value, opt)) {
			return *((int *)(*pattern_map).key);
		}
	}
	return -1;
}

int aeten_core_algebra__base_conv_from_10(char *output, unsigned int input, unsigned int obase, int flags) {
	int i, digit, length;
	unsigned int rest, out = 0;
	char digit_char;
	char str_buf[128];
	memset(str_buf, 0, 128);
	output[0]=0;

	out = input;
	do {
		sprintf(str_buf, "%u/%u", out, obase);
		rest = out%obase;
		out /= obase;
		if (rest>9) {
			digit_char = rest + 0x61 - 10;
		} else {
			digit_char = rest + 0x30;
		}
		if (AETEN_CORE__IS_VERBOSE(flags)) {
			printf("%s = %u remains %u(%c)\n", str_buf, out, rest, digit_char);
		}
		sprintf(str_buf, "%c%s", digit_char, output);
		strcpy(output, str_buf);

	} while (out!=0);

	return 0;
}

int aeten_core_algebra__base_conv_to_10(unsigned int *output, char* input, unsigned int ibase, int flags) {
	int i, digit, length;
	unsigned int rest, out = 0;
	char digit_char;
	char str_buf[128];
	memset(str_buf, 0, 128);

	length = strlen(input);
	char in[length];
	strcpy(in, input);
	aeten_core__to_lower_case(in);

	if (AETEN_CORE__IS_VERBOSE(flags)) {
		printf("%s(base %u) = ", in, ibase);
	}
	for (i=0; i<length;++i) {
		if ((ibase > 10) && (in[i] > 0x60)) {
			digit = in[i]-0x61+10;
		} else {
			digit = in[i]-0x30;
			if ((digit < 0) || (digit >= 10)) {
				return 1;
			}
		}
		if (digit>=ibase) {
			return 2;
		}
		if (AETEN_CORE__IS_VERBOSE(flags)) {
			if (i>0) {
				printf(" + ");
			}
			printf("%u*%u^%u", digit, ibase, length - i - 1);
		}
		out += digit*pow(ibase,(length - i - 1));
	}
	if (AETEN_CORE__IS_VERBOSE(flags)) {
		printf(" = %d(base 10)\n", out);
	}
	*output = out;
	return 0;
}

int aeten_core_algebra__base_conv(char *output, char* input, unsigned int ibase, unsigned int obase, int flags) {
	unsigned int out_10;
	output[0]=0;
	char *end;

	if (ibase == 10) {
		out_10 = strtoul(input, &end, 10);
		if (end == input) {
			return 1;
		}
	} else {
		if (0 != aeten_core_algebra__base_conv_to_10(&out_10, input, ibase, flags)) {
			return 1;
		}
		assert(out_10 == strtoul(input, &end, ibase));
	}
	if (obase == 10) {
		sprintf(output, "%u", out_10);
	} else {
		if (0 != aeten_core_algebra__base_conv_from_10(output, out_10, obase, flags)) {
			return 2;
		}
	}
	if (AETEN_CORE__IS_VERBOSE(flags)) {
		printf("%s(base %u) = %s(base %u)\n", input, ibase, output, obase);
	}

	return 0;
}

typedef enum algebra_base_opt_keys { VERBOSE, IBASE, OBASE } algebra_base_opt_keys_t;
static algebra_base_opt_keys_t verbose_opt_key = VERBOSE;
static algebra_base_opt_keys_t ibase_opt_key = IBASE;
static algebra_base_opt_keys_t obase_opt_key = OBASE;

int main(int argc, char**argv) {
	char out[21];
	int i, success;
	unsigned int flags = 0, ibase, obase;
	char *value;
	const static aeten_core_collections__map_entry_t algebra_base_opt[] = {
		{ &verbose_opt_key, "-v|--verbose" },
		{ &ibase_opt_key, "-i|--input-base" },
		{ &obase_opt_key, "-o|--output-base" }
	};
	for (i=1; i<argc; ++i) {
		switch(aeten_core__opt(algebra_base_opt, sizeof(algebra_base_opt)/sizeof(aeten_core_collections__map_entry_t), argv[i])) {
			case VERBOSE:
				flags |= AETEN_CORE__VERBOSE;
				break;
			case IBASE:
				ibase=atoi(argv[++i]);
				break;
			case OBASE:
				obase=atoi(argv[++i]);
				break;
			default:
				value=argv[i];
				break;
		}
	}
	printf("ibase=%u, obase=%u, value=%s\n", ibase, obase, value);
	success = aeten_core_algebra__base_conv(out, value, ibase, obase, flags);
	printf("%s\n", out);
	return success;
}
