#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "common.h"

int main(int argc, char* argv[]) {
    int * arr;
    int gamma = 0, epsilon = 0;
    int bufsize = 100;
    char line[bufsize];

    if (argc < 2) {
        perror("Missing argument: project_dir.\n");
        return 1;
    }

    const char *file_path = get_input_file(argv[1], 3);

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Failed to read file! %s\n", strerror(errno));
    }

    // Read first line, allocate bit arr.
    fscanf(fp, "%s", &line);
    size_t bitlen = strlen(line);
    arr = (int *) malloc(sizeof(int) * bitlen);
    memset(arr, 0, bitlen*sizeof(int));

    // Sum bit frequencies for each position. <0 == 0, >0 == 1
    do {
        char * t;
        int i = 0;
        for(t = line; *t != '\0'; t++) {
            switch(t[0]) {
                case '0':
                    arr[i]--;
                    break;
                case '1':
                    arr[i]++;
                    break;
            }
            i++;
        }
    } while(fscanf(fp, "%s", &line) == 1);

    // Print arr.
    int power;
    for(int i=0; i<bitlen; i++) {
        power = pow(2, bitlen-i-1);
        if (arr[i] < 0) {
            epsilon += power;
        } else {
            gamma += power;
        }
    }

    // Release resources.
    free(arr);

    printf("Part1: %d\n", gamma * epsilon);

    return 0;
}