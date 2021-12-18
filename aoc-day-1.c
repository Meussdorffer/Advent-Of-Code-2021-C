#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void part_1() {
    int cur_num, last_num = 0;
    int increments = 0;

    // Read input file into data.
    FILE *fp = fopen("C:\\Users\\JackM\\CLionProjects\\advent-of-code-2021\\input\\day-1.txt", "r");
    if (fp == NULL) {
        printf("Failed to read file! %s\n", strerror(errno));
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

    printf("Num increments: %d\n", increments);
}

void part_2() {
    int first_num, second_num, third_num = 0;
    int cur_sum, prev_sum = 0;
    int increments = 0;

    // Read input file into data.
    FILE *fp = fopen("C:\\Users\\JackM\\CLionProjects\\advent-of-code-2021\\input\\day-1.txt", "r");
    if (fp == NULL) {
        printf("Failed to read file! %s\n", strerror(errno));
    }

    int i = 0;
    while(fscanf(fp, "%d", &first_num) == 1) {
        cur_sum = first_num + second_num + third_num;
        if (i >= 2 && cur_sum > prev_sum) {
            increments++;
        }
        third_num = second_num;
        second_num = first_num;
        prev_sum = cur_sum;
        i++;
    }
    fclose(fp);

    printf("Num three-window increments: %d\n", increments);
}

int main() {
    part_1();
    part_2();
    return 0;
}
