/*
 *  unit_tests.h
 *  Angela Huynh (ahuynh02) and Zach Everett (zevere01)
 *  September 12, 2024
 *
 *  Purpose: CS 40 header file that contains unit testing functions
 *   for homework assignment arith 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pnm.h>
#include <uarray2b.h>
#include <uarray2.h>
#include "a2methods.h"
#include "a2blocked.h"
#include "a2plain.h"
#include "compress40.h"
#include <assert.h>


void compress40_test0(FILE* input)
{
        compress40(input);
}



int main(int argc, char *argv[])
{
        if (argc != 2) {
                fprintf(stderr, "cant open file\n");
                return 1;
        }

        FILE *file = strcmp(argv[1], "-") == 0 ? stdin : fopen(argv[1], "rb");
        if (!file) {
                fprintf(stderr, "Error: Could not open input files.\n");
                fclose(file);
                return 1;
        }
        compress40_test0(file);
}
