#ifndef NUM_CONVERT_H
#define NUM_CONVERT_H

#define ERR_NO_ARGS (-1)
#define ERR_INVALID_ARG (-2)

#define MAX_BIT_LENGTH (32) /* Maximum bits to be considered for conversion */


const char *err_messages[] = {
    "Unknown error.",
    "Too few arguments.",
    "Invalid argument(s)."
};

void print_usage();
void print_err(int err);
int parse_arg(char *number);
void parse_binary(char *number);

#endif
