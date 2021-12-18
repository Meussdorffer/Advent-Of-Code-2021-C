#include <stdio.h>
#include <string.h>
#define PATH_LEN 100

const char* get_input_file(const char* project_dir, const int day_num) {
    char file_stem[20];
    sprintf(file_stem, "\\input\\day-%d.txt", day_num);

    static char input_filepath[PATH_LEN];
    input_filepath[0] = '\0';
    strncat(input_filepath, project_dir, PATH_LEN - 1);
    strncat(input_filepath, file_stem, PATH_LEN - 1);

    return input_filepath;
}
