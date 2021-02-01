#ifndef HEXIDECINARY_H
#define HEXIDECINARY_H

#define ERR_NO_ARGS (-1)
#define ERR_INVALID_ARG (-2)

#define SIXTYFOUR_BIT
/*
#define THIRTYTWO_BIT
*/
#ifdef THIRTYTWO_BIT
#define MAX_BIT_LENGTH (32) /* Maximum bits to be considered for conversion */
#define MAX_NIBBLE_LENGTH (MAX_BIT_LENGTH / 4)
#define MAX_DEC_LENGTH (10)
#define BIN_MASK (0x800000000)
#endif

#ifdef SIXTYFOUR_BIT
#define MAX_BIT_LENGTH (64) /* Maximum bits to be considered for conversion */
#define MAX_NIBBLE_LENGTH (MAX_BIT_LENGTH / 2)
#define MAX_DEC_LENGTH (20)
#define BIN_MASK (0x8000000000000000)
#endif


const char *err_messages[] = {
    "Unknown error.",
    "Too few arguments.",
    "Invalid argument(s)."
};

void print_usage();
void print_err(int err);
int parse_arg(char *number);
void parse_binary(const char *number);
void parse_hex(const char *number);
void parse_decimal(const char *number);
void print_binary(long decimal);

#endif
