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
    fclose(fp);

    return 0;
}