#ifndef HEXIDECINARY_H
#define HEXIDECINARY_H


#define SIXTYFOUR_BIT
/*
#define THIRTYTWO_BIT
*/

#ifdef THIRTYTWO_BIT
#define MAX_BIT_LENGTH (32) /* Maximum bits to be considered for conversion */
#define MAX_NIBBLE_LENGTH (MAX_BIT_LENGTH / 4)
#define MAX_DEC_LENGTH (10)
#define BIN_MASK (0x80000000)
#endif

#ifdef SIXTYFOUR_BIT
#define MAX_BIT_LENGTH (64) /* Maximum bits to be considered for conversion */
#define MAX_NIBBLE_LENGTH (MAX_BIT_LENGTH / 2)
#define MAX_DEC_LENGTH (20)
#define BIN_MASK (0x8000000000000000)
#endif


#define ERR_NO_ARGS (-1)
#define ERR_INVALID_ARG (-2)
#define EXIT_EARLY_NO_ERR (-3)
#define ERR_INVALID_FLAG (-4)
#define ERR_FILE_OPEN_FAIL (-5)

const char *err_message[] = {
    "Unknown error.",
    "Too few arguments.",
    "Invalid argument(s).",
    "Program completed successfully.",
    "Invalid flag.",
    "Unable to open file."
};

void print_usage();
void print_err(int err);
int print_help(const char *prog);
int parse_flags(const char *prog, const char *flag);
int parse_arg(char *number);
void parse_binary(const char *number);
void parse_hex(const char *number);
void parse_decimal(const char *number);
void print_binary(long decimal);

#endif
