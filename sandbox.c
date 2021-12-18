#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "common.h"

int main(int argc, char* argv[]) {

    const char* input_filepath = get_input_file(argv[1], 2);
    printf("Filepath is: %s", input_filepath);

    FILE *fp = fopen(input_filepath, "r");
    if (fp == NULL) {
        printf("Failed to read file! %s\n", strerror(errno));
        return 1;
    }

    int i = 0;
    while(fscanf(fp, "%d", &cur_num) == 1) {
        if (i >= 1 && cur_num > last_num) {
            increments++;
        }
        last_num = cur_num;
        i++;
    }
    fclose(fp);

    return 0;
}