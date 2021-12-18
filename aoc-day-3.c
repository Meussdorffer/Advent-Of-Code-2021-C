#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void part_1() {
    int * arr;
    int gamma = 0, epsilon = 0;
    int bufsize = 100;
    char line[bufsize];

    // Read input file into data.
    FILE *fp = fopen("C:\\Users\\JackM\\CLionProjects\\advent-of-code-2021\\input\\day-3.txt", "r");
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

    printf("Gamma: %d, Epsilon: %d, Power Consumption: %d\n", gamma, epsilon, gamma * epsilon);

    // Release resources.
    free(arr);
}


int main() {
    part_1();
//    part_2();
    return 0;
}