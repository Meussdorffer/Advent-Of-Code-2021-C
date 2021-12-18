#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


int main(int argc, char* argv[]) {
    int cur_num;
    int last_num = 0;
    int third_num = 0;

    int cur_sum;
    int prev_sum;

    int increments1 = 0;
    int increments2 = 0;

    if (argc < 2) {
        perror("Missing argument: project_dir.\n");
        return 1;
    }

    const char *file_path = get_input_file(argv[1], 1);

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Failed to read file! %s\n", strerror(errno));
        return 1;
    }

    int i = 0;
    while(fscanf(fp, "%d", &cur_num) == 1) {
        // Part 1
        if (i >= 1 && cur_num > last_num) {
            increments1++;
        }

        // Part 2
        cur_sum = cur_num + last_num + third_num;
        if (i > 2 && cur_sum > prev_sum) {
            increments2++;
        }

        third_num = last_num;
        last_num = cur_num;
        prev_sum = cur_sum;
        i++;
    }
    fclose(fp);

    printf("Part1: %d\n", increments1);
    printf("Part2: %d\n", increments2);
    return 0;
}
