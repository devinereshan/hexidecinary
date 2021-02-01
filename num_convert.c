/*
 * Accepts a binary, hexidecimal, or decimal integer from the command line, and
 * displays it along with it's equivalent representation in the other formats.
 *
 * Written by Devin Ereshan.
 *
 */
#include <stdio.h>

#include "num_convert.h"


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
        } else if (number[1] == 'x' || number[1] == 'X') {
            /* TODO: call hex function */
        }
    } else if (number[0] > '0' && number[0] <= '9') {
        /* TODO: call decimal function */
    }

    /* Otherwise, not a valid number representation */
    return ERR_INVALID_ARG;
}
