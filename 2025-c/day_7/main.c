#include <string.h>

#include "read_file.h"

int part_1_solver(char array[MAX_ROWS][MAX_COLUMNS], int row_size) {

    int count_splits = 0;
    int column_length = strlen(array[0]);

    char above_row[column_length];
    char current_row[column_length];
    char above, current;

    for (int row = 1; row < row_size; row++) {

        // copies lines information
        strncpy(above_row, array[row-1], column_length);
        strncpy(current_row, array[row], column_length);

        for (int col = 0; col < column_length-1; col++){

            // copies char information
            above = above_row[col];
            current = current_row[col];

            // checks for starting point(s)
            if (above == 'S') {
                current_row[col] = '|';
            } 
            // checks for beam
            else if (above == '|') {
                // checks for splitting
                if (current == '^') {
                    if (col-1 >= 0 && current_row[col-1] != '^') {
                        current_row[col-1] = '|';
                    }
                    if (col+1 < column_length && current_row[col+1] != '^') {
                        current_row[col+1] = '|';
                    }
                    count_splits++;
                }
                else {
                    current_row[col] = '|';
                }
            }
        }
        strncpy(array[row], current_row, column_length);
    }

    return count_splits;
}

long sum_array(long * array, int length) {
    long sum = 0;

    for (int i = 0; i < length; i++) {
        printf("%ld %ld\n", array[i], sum);
        sum = sum + array[i];
    }
    return sum;
}

long part_2_solver(char array[MAX_ROWS][MAX_COLUMNS], int row_size) {

    int column_length = strlen(array[0]);
    long answer;
    long memory_timelines[column_length];
    memset(memory_timelines, 0, column_length * sizeof(long));

    char above_row[column_length];
    char current_row[column_length];
    char above, current;

    for (int row = 1; row < row_size; row++) {

        // copies lines information
        strncpy(above_row, array[row-1], column_length);
        strncpy(current_row, array[row], column_length);

        for (int col = 0; col < column_length-1; col++){

            // copies char information
            above = above_row[col];
            current = current_row[col];

            // checks for starting point(s)
            if (above == 'S') {
                current_row[col] = '|';
                memory_timelines[col] = 1;
            } 
            // checks for beam
            else if (above == '|') {
                // checks for splitting
                if (current == '^') {
                    if (col-1 >= 0 && current_row[col-1] != '^') {
                        current_row[col-1] = '|';
                        memory_timelines[col-1] += memory_timelines[col];
                    }
                    if (col+1 < column_length && current_row[col+1] != '^') {
                        current_row[col+1] = '|';
                        memory_timelines[col+1] += memory_timelines[col];
                    }
                    memory_timelines[col] = 0;
                }
                else {
                    current_row[col] = '|';
                }
            }
        }
        strncpy(array[row], current_row, column_length);
    }
    
    answer = sum_array(memory_timelines, column_length);
    return answer;
}

int main() {

    char * filename = "data.txt";
    char array[MAX_ROWS][MAX_COLUMNS];

    int row_size = read_file(filename, array);
    int part_1_solution;

    long part_2_solution;

    // for (int i = 0; i < row_size; i++) {
    //     printf("%s", array[i]);
    // }
    // printf("\n");

    part_1_solution = part_1_solver(array, row_size);
    printf("Day 7 Part 1: %d\n", part_1_solution);

    // must reload because part 1 updates array
    row_size = read_file(filename, array);
    part_2_solution = part_2_solver(array, row_size);
    printf("Day 7 Part 2: %ld\n", part_2_solution);

    return 1;
}