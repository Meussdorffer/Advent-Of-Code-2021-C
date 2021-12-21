#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "common.h"

const int BITSTR_SIZE = 100;
enum rating{oxygen, co2};

int calc_rating(const char ** bit_strings, int n_strings, enum rating bit_criteria) {
    int bit_len=strlen(bit_strings[0]);

    // Init a lookup table that will be pruned on each iteration.
    int num_bits = n_strings;
    char ** bits_table = malloc(sizeof(char*) * n_strings);
    for(int i=0; i<n_strings; i++) bits_table[i] = (char *) bit_strings[i];

    // Reduce lookup table until one bit string remains.
    char * final_bit_str;
    for(int bit_idx=0; bit_idx < bit_len; bit_idx++) {
        // Get "mode" bit.
        int ones = 0;
        int zeros = 0;
        char mode;
        for (int i = 0; i < n_strings; i++) {
            if (bits_table[i] != NULL) {
                switch (bits_table[i][bit_idx]) {
                    case '0':
                        zeros++;
                        break;
                    case '1':
                        ones++;
                        break;
                    default:
                        break;
                }
            }
        }
        switch (bit_criteria) {
            case oxygen:
                mode = (ones >= zeros) ? '1' : '0'; // most common bit, break ties with 1.
                break;
            case co2:
                mode = (ones >= zeros) ? '0' : '1'; // least common bit, break ties with 0.
                break;
            default:
                perror("Unknown bit_criteria encountered.");
                return -1;
        }

        // Remove non-mode bit strings from table.
        for (int i = 0; i < n_strings; i++) {
            if (bits_table[i] != NULL && bits_table[i][bit_idx] != mode) {
                bits_table[i] = NULL;
                num_bits--;
            }
        }

        // Debug: print remaining bit strings.
        // printf("\n\nRemaining strings:\n");
        // for (int i = 0; i < n_strings; i++) {
        //     if (bits_table[i] != NULL) printf("%s\n", bits_table[i]);
        // }

        // Get the final bit string.
        if (num_bits == 1) {
            for (int i = 0; i < n_strings; i++) {
                if (bits_table[i] != NULL) {
                    final_bit_str = bits_table[i];
                    break;
                }
            }
        }
    }

    // Deallocate.
    free(bits_table);

    return btoi(final_bit_str);
}

int main() {
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
        power = (int) pow(2, (int) bitlen-i-1);
        if (arr[i] < 0) {
            epsilon += power;
        } else {
            gamma += power;
        }
    }

    // Calculate part2 result.
    int oxy_rating = calc_rating((const char **) bitstr_arr, num_bitstrs, oxygen);
    int co2_rating = calc_rating((const char **) bitstr_arr, num_bitstrs, co2);

    printf("Part1: %d\n", gamma * epsilon);
    printf("Part2: %d\n", oxy_rating * co2_rating);

    // Deallocate.
    free(arr);
    for(int i=0; i < num_bitstrs; i++) {
        free(bitstr_arr[i]);
    }
    free(bitstr_arr);


    return 0;
}