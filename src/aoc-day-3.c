#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "common.h"

const int BITSTR_SIZE = 100;

int main(int argc, char* argv[]) {
    int * arr = NULL;
    int gamma = 0, epsilon = 0;
    int num_bitstrs;
    char ** bitstr_arr;

    // Open file.
    FILE *fp = get_input_file(3);

    // Allocate & populate array of bitstrings.
    // Also do most of part1 within the loop.
    size_t bitlen;
    num_bitstrs = get_num_file_lines(fp);
    bitstr_arr = (char**) malloc(sizeof(char*) * num_bitstrs);
    for(int i=0; i < num_bitstrs; i++) {
        bitstr_arr[i] = (char *) malloc(BITSTR_SIZE);
        fscanf(fp, "%s", bitstr_arr[i]);

        // Part 1.
        // Init arr, bitlen if first loop.
        if (arr == NULL) {
            bitlen = strlen(bitstr_arr[i]);
            arr = (int *) calloc(bitlen, sizeof(int));
        }

        // Sum bit frequencies for each position. <0 == 0, >0 == 1
        int j = 0;
        for(char * t = bitstr_arr[i]; *t != '\0'; t++) {
            switch(t[0]) {
                case '0':
                    arr[j]--;
                    break;
                case '1':
                    arr[j]++;
                    break;
            }
            j++;
        }
    }

    // Calculate part1 result.
    int power;
    for(int i=0; i<bitlen; i++) {
        power = pow(2, bitlen-i-1);
        if (arr[i] < 0) {
            epsilon += power;
        } else {
            gamma += power;
        }
    }

    // Calculate part2 result.
    // int valid_strs = num_bitstrs;
    // int * valid_str_idxs = malloc(sizeof(int) * num_bitstrs);
    // memset(valid_str_idxs, 1, num_bitstrs);
    //
    // int bitidx = 0;
    // int bestidx;
    // while(valid_strs > 0) {
    //     int zeros = 0;
    //     int ones = 0;
    //
    //     // Sum the bit occurrences in the bitidx'th position.
    //     for(int i=0; i < num_bitstrs; i++) {
    //         if (valid_str_idxs[i]) {
    //             switch (bitstr_arr[i][bitidx]) {
    //                 case '0':
    //                     zeros++;
    //                     break;
    //                 case '1':
    //                     ones++;
    //                     break;
    //             }
    //         }
    //     }
    //
    //     char mode_char;
    //     if (zeros > ones) {
    //         mode_char = "0";
    //     } else {
    //         mode_char = "1";
    //     }
    //
    //     for(int i=0; i < num_bitstrs; i++) {
    //         if (valid_str_idxs[i] && (bitstr_arr[i][bitidx] != mode_char)) {
    //             valid_str_idxs[i] = 0;
    //             valid_strs--;
    //         }
    //     }
    //
    //     if (valid_strs == 1) {
    //         for(int i=0; i < num_bitstrs; i++) {
    //             bestidx = i;
    //             if (valid_str_idxs[i] == 1) break;
    //         }
    //         valid_strs = 0;
    //     }
    // }

    printf("Part1: %d\n", gamma * epsilon);
    // printf("Part2: %s\n", bitstr_arr[bestidx]);

    // Release resources.
    free(arr);
    for(int i=0; i < num_bitstrs; i++) {
        free(bitstr_arr[i]);
    }
    free(bitstr_arr);


    return 0;
}