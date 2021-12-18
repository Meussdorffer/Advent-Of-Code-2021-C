#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "common.h"


int main(int argc, char* argv[]) {
    int horiz = 0;
    int depth1 = 0;
    int depth2 = 0;
    int aim = 0;

    int mov = 0;
    char dir[10];

    if (argc < 2) {
        perror("Missing argument: project_dir.\n");
        return 1;
    }

    const char *file_path = get_input_file(argv[1], 2);

    // Read input file into data.
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Failed to read file! %s\n", strerror(errno));
    }

    while(fscanf(fp, "%s %d", &dir, &mov) == 2) {
        if (strcmp(dir, "forward") == 0) {
            horiz += mov;
            depth2 += mov * aim;
        }
        else if (strcmp(dir, "up") == 0) {
            depth1 -= mov;
            aim -= mov;
        }
        else if (strcmp(dir, "down") == 0) {
            depth1 += mov;
            aim += mov;
        }
        else {
            printf("Invalid input %s");
            return 1;
        }
    }

    fclose(fp);

    printf("Part1: %d\n", horiz * depth1);
    printf("Part2: %d\n", horiz * depth2);

    return 0;
}
