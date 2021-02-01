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
            /* TODO: consider possible errors and return them if possible */
            parse_binary(number);
            return 0;
        } else if (number[1] == 'x' || number[1] == 'X') {
            /* TODO: consider possible errors and return them if possible */
            parse_hex(number);
            return 0;
        }
    } else if (number[0] > '0' && number[0] <= '9') {
        /* TODO: consider possible errors and return them if possible */
        parse_decimal(number);
        return 0;
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
    long digits[MAX_BIT_LENGTH];
    int i, k;
    char c;
    long decimal;

    /* skip the leading '0b' */
    num += 2;

    for (i = 0, c = *num; c != '\0' && i < MAX_BIT_LENGTH; c = *(++num)) {
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
    printf("dec: %lu\nhex: 0x%lx\nbin: ", decimal, decimal);
    print_binary(decimal);
    putchar('\n');
}

void parse_hex(const char *num) {
    long digits[MAX_NIBBLE_LENGTH];
    int i, k;
    unsigned char c;
    long decimal;

    /* skip the leading '0x' */
    num += 2;

    for (i = 0, c = *num; c != '\0' && i < MAX_NIBBLE_LENGTH; c = *(++num)) {
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
        /* bit shift each digit by 4 * its magnitude */
        decimal += digits[k] << ((i - (k + 1)) * 4);
    }

    printf("dec: %lu\nhex: 0x%lx\nbin: ", decimal, decimal);

    print_binary(decimal);
    putchar('\n');
}

/*
 * Any invalid digits will be discarded.
 * Prints an unsigned decimal representation of num.
 * Will overflow in a predictable manner relative to MAX_DEC_LENGTH
 */
void parse_decimal(const char *num) {
    long decimal;
    long digits[MAX_DEC_LENGTH];
    int i;
    long k;
    unsigned char c;

    for (i = 0, c = *num; *num != '\0' && i < MAX_DEC_LENGTH; c = *(++num)) {
        if (c >= '0' && c <= '9') {
            digits[i++] = c - '0';
        }
    }

    for (decimal = 0, k = 1; i > 0;) {
        decimal += digits[--i] * k;
        k *= 10;
    }

    printf("dec: %lu\nhex: 0x%lx\nbin: ", decimal, decimal);

    print_binary(decimal);
    putchar('\n');
}

void print_binary(long decimal) {
    unsigned long mask;
    int i, k;

    printf("0b");
    if (decimal == 0) {
        putchar('0');
        return;
    }

    /* clear insignificant leading zeros */
    for (mask = BIN_MASK, i = 0; (decimal & mask) == 0; mask >>= 1, i++);
    /*
    for (mask = 0x80000000, i = 0; (decimal & mask) == 0; mask >>= 1, i++);
    */

    for (k = 0; i < MAX_BIT_LENGTH; mask >>= 1, i++, k++) {
        if (k > 0 && i % 4 == 0) {
            putchar(' ');
        }
        printf("%d", decimal & mask ? 1 : 0);
    }

}
