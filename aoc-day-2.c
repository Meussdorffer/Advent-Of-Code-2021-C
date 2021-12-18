#include <stdio.h>
#include <string.h>
#include <errno.h>

void part_1() {
    int hpos = 0, vpos = 0;
    int mov = 0;
    char dir[10];

    // Read input file into data.
    FILE *fp = fopen("C:\\Users\\JackM\\CLionProjects\\advent-of-code-2021\\input\\day-2.txt", "r");
    if (fp == NULL) {
        printf("Failed to read file! %s\n", strerror(errno));
    }

    while(fscanf(fp, "%s %d", &dir, &mov) == 2) {
        if (strcmp(dir, "forward") == 0) {
            hpos += mov;
        }
        else if (strcmp(dir, "up") == 0) {
            vpos -= mov;
        }
        else if (strcmp(dir, "down") == 0) {
            vpos += mov;
        }
        else {
            printf("Invalid input %s");
            return;
        }
    }

    printf("Result of vertical_pos * horizontal_pos: %d\n", hpos * vpos);

    fclose(fp);

}

void part_2() {
    int hpos = 0, aim = 0, depth = 0;
    int mov = 0;
    char dir[10];

    // Read input file into data.
    FILE *fp = fopen("C:\\Users\\JackM\\CLionProjects\\advent-of-code-2021\\input\\day-2.txt", "r");
    if (fp == NULL) {
        printf("Failed to read file! %s\n", strerror(errno));
    }

    while(fscanf(fp, "%s %d", &dir, &mov) == 2) {
        if (strcmp(dir, "forward") == 0) {
            hpos += mov;
            depth += mov * aim;
        }
        else if (strcmp(dir, "up") == 0) {
            aim -= mov;
        }
        else if (strcmp(dir, "down") == 0) {
            aim += mov;
        }
        else {
            printf("Invalid input %s");
            return;
        }
    }

    printf("Result of horizontal_pos * depth: %d\n", hpos * depth);

    fclose(fp);

}

int main() {
    part_1();
    part_2();
    return 0;
}
