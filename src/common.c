#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>

const int MAX_PATH_SIZE = 250;
const int MAX_ERR_MSG_LEN = 1000;

FILE* get_input_file(const int day_num) {
    char path[MAX_PATH_SIZE];
    char file_stem[30];

    path[0] = '\0';
    getcwd(path, sizeof(path));
    sprintf(file_stem, "/../input/day-%d.txt", day_num);
    strncat(path, file_stem, MAX_PATH_SIZE - 1);

    // debug.
    // printf("Path: %s\n", path);

    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        char msg[MAX_ERR_MSG_LEN];
        sprintf(msg, "Failed to open file %s", path);
        perror(msg);
        exit(EXIT_FAILURE);
    }

    return fp;
}

int get_num_file_lines(FILE* fp) {
    int num_lines = 1;
    char ch;

    while(!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') num_lines++;
    }

    rewind(fp);

    return num_lines;
}

int btoi(const char * bit_str) {
    size_t bitlen = strlen(bit_str);
    int power = 0;
    for(int i=0; i<bitlen; i++) {
        if (bit_str[i] == '1')
            power += (int) pow(2, (int) bitlen-i-1);
    }

    return power;
}
