#ifndef ADVENT_OF_CODE_2021_COMMON_H
#define ADVENT_OF_CODE_2021_COMMON_H

#include <stdbool.h>

FILE* get_input_file(int day_num);

const int get_num_file_lines(FILE* fp);

int btoi(char * bit_str);

bool is_line_end(const char * str);

#endif //ADVENT_OF_CODE_2021_COMMON_H

