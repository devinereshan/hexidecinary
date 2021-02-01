/*
 * Accepts a binary, hexidecimal, or decimal integer from the command line, and
 * displays it along with it's equivalent representation in the other formats.
 *
 * Written by Devin Ereshan.
 *
 */
#include <stdio.h>

#include "hexidecinary.h"


void print_usage();
void print_err(int err);
int parse_arg(char *number);

int main(int argc, char **argv) {
    int err;
    char *number;

    /* ensure argv[1] exists */
    if (argc < 2) {
        err = ERR_NO_ARGS;
        print_err(err);
        print_usage(argv[0]);
        return err;
    }

    number = argv[1];

    if (number[0] == '\0') {
        err = ERR_INVALID_ARG;
        print_err(err);
        print_usage(argv[0]);
        return ERR_INVALID_ARG;
    }

    /* check for help flag */
    /* TODO */

    if ((err = parse_arg(number)) < 0) {
        print_err(err);
        print_usage(argv[0]);
        return err;
    }

    return 0;
}

void print_usage(const char *prog) {
    printf("Usage:\n  %s <number>\n"
            "\n<number> must be a valid decimal, binary, or"
            "\nhexadecimal representation of a 32-bit number."
            "\n\nType: '%s -h' or '%s --help' for more information.\n",
            prog, prog, prog);

}

void print_err(int err) {
    printf("ERROR: %s\n", err_messages[-err]);
}


int parse_arg(char *number) {
    if (number[0] == '0') {
        /* check for bin or hex */
        if (number[1] == 'b' || number[1] == 'B') {
            /* TODO: call binary function */
            parse_binary(number);
            return 0;
        } else if (number[1] == 'x' || number[1] == 'X') {
            /* TODO: call hex function */
            parse_hex(number);
            return 0;
        }
    } else if (number[0] > '0' && number[0] <= '9') {
        /* TODO: call decimal function */
    }

    /* Otherwise, not a valid number representation */
    return ERR_INVALID_ARG;
}

/* Parses the binary representation of a number and prints its hexidecimal
 * and unsigned decimal equivalents.
 * Reads a maximum of MAX_BIT_LENGTH (32) bits.
 * Ignores spaces, but interprets any other characters as 1, except for '0',
 * which is interpreted as zero.
 */
void parse_binary(const char *num) {
    int digits[MAX_BIT_LENGTH];
    int i, k;
    char c;
    int decimal;
    const char *orig_num;

    orig_num = num;

    /* skip the leading '0b' */
    num += 2;

    for (i = 0, c = *num; i < MAX_BIT_LENGTH && c != '\0'; c = *(++num)) {
        /* ignore everything except '1' or '0' */
        if (c == '0') {
            digits[i++] = 0;
        } else if (c == '1') {
            digits[i++] = 1;
        }
    }

    decimal = 0;
    for (k = 0; k < i; k++) {
        decimal += digits[k] << (i - (k + 1));
    }

    /* TODO: replace printing original binary string new function that
     * prints the digits array. So that meaningless digits aren't echoed
     * back to the user.
     */
    printf("dec: %u\nhex: 0x%x\nbin: %s\n", decimal, decimal, orig_num);
}

void parse_hex(const char *num) {
    int digits[MAX_NIBBLE_LENGTH];
    int i, k;
    unsigned char c;
    int decimal;
    const char *orig_num;

    orig_num = num;

    /* skip the leading '0x' */
    num += 2;

    for (i = 0, c = *num; i < MAX_NIBBLE_LENGTH && c != '\0'; c = *(++num)) {
        /* Compute the numeric value of the digit. */
        if (c <= 57) {
            c -= 48;
        } else if (c <= 102) {
            c -= 87;
        }

        if (c < 16) {
            digits[i++] = (int) c;
        }
    }

    decimal = 0;
    for (k = 0; k < i; k++) {
        /* bit shift each digit by 4 * it's magnitude */
        decimal += digits[k] << ((i - (k + 1)) * 4);
    }

    /* TODO: print binary */
    printf("dec: %u\nhex: 0x%x\n", decimal, decimal);
}

void print_binary(int decimal) {

}

