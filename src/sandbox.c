#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include "common.h"

int main(int argc, char* argv[]) {
    FILE *fp = get_input_file(2);

    char * line = NULL;
    size_t line_len = 0;
    ssize_t nread;
    while((nread = getline(&line, &line_len, fp)) != -1) {
        printf("%s", line);
    }

    fclose(fp);
    free(line);
    return 0;
}