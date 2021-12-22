#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "common.h"

const int NUM_POSSIBLE_BOARDS = 100;
const int NUM_BUFF_SIZE = 10;
const int LARGEST_POSSIBLE_BOARD_NUM = 100;
const char SPACE = ' ';
const char NEWLINE[3] = "\r\n";

typedef struct board {
    bool * num_lookup;
} board;

board * board_init() {
    board * newBoard = (board *) malloc(sizeof(board));
    newBoard->num_lookup = (bool *) calloc(LARGEST_POSSIBLE_BOARD_NUM, sizeof(int));
    return newBoard;
}

int read_board_data(FILE * fp, board * bingo_boards[]) {
    char * line = NULL;
    size_t line_size;
    int n_drawn_numbers = 1;
    int * drawn_numbers;
    char * num_buff = (char *) malloc(sizeof(char) * NUM_BUFF_SIZE);
    int num_boards = 0;

    // Read drawn numbers into dynamically allocated int array.
    getline(&line, &line_size, fp);
    for (int i=0; i<line_size; i++)
        if (line[i] == ',') n_drawn_numbers++;
    drawn_numbers = (int *) malloc(sizeof(int) * n_drawn_numbers);
    drawn_numbers[0] = atoi(strtok(line, ","));
    for (int i=1; i<n_drawn_numbers; i++)
        drawn_numbers[i] = atoi(strtok(NULL, ","));

    // Read board data in.
    while(getline(&line, &line_size, fp) != -1) {
        if (is_line_end(line)) {
            num_boards++;
            bingo_boards[num_boards - 1] = board_init();
        } else {
            while(!is_line_end(line) && !isblank(line[0])) {
                // Clear leading spaces.
                while(line[0] == SPACE) {
                    line++;
                }

                // Read next number into board lookup.
                char *spc = strchr(line, SPACE);
                char *delim = (spc == NULL) ? strstr(line, NEWLINE) : spc; // delim could be space or EOL.
                int stop_pos = (int) (delim - line);
                if (delim == NULL) {
                    stop_pos = strlen(line);
                }
                memset(num_buff, '\0', NUM_BUFF_SIZE);
                strncpy(num_buff, line, stop_pos);
                bingo_boards[num_boards - 1]->num_lookup[atoi(num_buff)] = true;

                // Continue to next num in line.
                line += stop_pos;
            }
        }
    }

    return num_boards;
}

int main() {
    char * line = NULL;
    size_t line_size;
    int n_drawn_numbers = 1;
    int * drawn_numbers;
    char board_char;
    board * bingo_boards[NUM_POSSIBLE_BOARDS];
    char * num_buff = (char *) malloc(sizeof(char) * NUM_BUFF_SIZE);
    int num_boards = -1;

    // Open file.
    FILE *fp = get_input_file(4);
    num_boards = read_board_data(fp, bingo_boards);

    // Read drawn numbers into dynamically allocated int array.
    // getline(&line, &line_size, fp);
    // for (int i=0; i<line_size; i++)
    //     if (line[i] == ',') n_drawn_numbers++;
    // drawn_numbers = (int *) malloc(sizeof(int) * n_drawn_numbers);
    // drawn_numbers[0] = atoi(strtok(line, ","));
    // for (int i=1; i<n_drawn_numbers; i++)
    //     drawn_numbers[i] = atoi(strtok(NULL, ","));
    //
    // Read board data in.
    // while(getline(&line, &line_size, fp) != -1) {
    //     if (is_line_end(line)) {
    //         num_boards++;
    //         bingo_boards[num_boards] = board_init();
    //     } else {
    //         while(!is_line_end(line) && !isblank(line[0])) {
    //             // Clear leading spaces.
    //             while(line[0] == SPACE) {
    //                 line++;
    //             }
    //
    //             // Read next number into board lookup.
    //             char *spc = strchr(line, SPACE);
    //             char *delim = (spc == NULL) ? strstr(line, NEWLINE) : spc; // delim could be space or EOL.
    //             int stop_pos = (int) (delim - line);
    //             if (delim == NULL) {
    //                 stop_pos = strlen(line);
    //             }
    //             memset(num_buff, '\0', NUM_BUFF_SIZE);
    //             strncpy(num_buff, line, stop_pos);
    //             bingo_boards[num_boards]->num_lookup[atoi(num_buff)] = true;
    //
    //             // Continue to next num in line.
    //             line += stop_pos;
    //         }
    //     }
    // }

    // Debug: print boards.
    for(int i=0; i<=num_boards; i++) {
        printf("Board %d: [", i);
        for(int j=0; j<LARGEST_POSSIBLE_BOARD_NUM; j++) {
            printf("%d, ", bingo_boards[i]->num_lookup[j]);
        }
        printf("]\n");
    }



    // Deallocate.
    fclose(fp);
    free(drawn_numbers);
    free(num_buff);
    for(int i=0; i<num_boards; i++) {
        free(bingo_boards[i]->num_lookup);
        free(bingo_boards[i]);
    }

    return 0;
}
