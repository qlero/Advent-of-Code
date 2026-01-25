#include <limits.h>
#include <string.h>

#include "readfile.h"

int find_shortest_row(char array[MAX_ROWS][MAX_COLUMNS], int row_count) {

    int min_len_row_count = INT_MAX;
    int length;

    // skipping the operator row
    for (int i = 0; i < row_count-1; i++) {
        length = strlen(array[i]);
        if (min_len_row_count > strlen(array[i])) {
            min_len_row_count = length;
        }
    }

    return min_len_row_count;
}

long long solve_part1(char array[MAX_ROWS][MAX_COLUMNS], int row_count, int col_count, int intermediary_prints){

    // declares placeholder variables
    int blank_array_location_check, record_condition_1, record_condition_2;

    long long placeholder_number_array[row_count-1];
    long long placeholder_multiplier_array[row_count-1];
    long long temp_acc;
    long long accumulator = 0;

    char placeholder_operator = ' ';

    // Initializes arrays
    for (int i = 0; i < row_count-1; i++) {
        placeholder_number_array[i] = 0;
        placeholder_multiplier_array[i] = 1;
    }

    

    // backtrack logic
    for (int col = col_count-1; col >= 0; col--){
        printf("-- %lld ---\n", placeholder_number_array[0]);
        // Resets placeholder variables
        blank_array_location_check = 0;
        // Iterates over a column
        for (int row = 0; row < row_count-1; row++) {
            // Increments counter if location empty
            if (array[row][col] == ' ') {
                blank_array_location_check++;
            } else {
                printf("%lld ", (array[row][col] - '0'));
                placeholder_number_array[row] += (array[row][col] - '0') * placeholder_multiplier_array[row];
                placeholder_multiplier_array[row] *= 10;
            }
            // Retrieves operator
            if (array[row_count-1][col] != ' ') {
                placeholder_operator = array[row_count-1][col];
            }
            if (intermediary_prints) {
                printf("Inter row %d col %d (%d/%d) %c \n", row, col, blank_array_location_check, row_count-1, placeholder_operator);
            }

            printf("%lld\n", placeholder_number_array[0]);
        }
        
        // Performs accumulation
        record_condition_1 = blank_array_location_check == row_count-1 && array[row_count-1][col] == ' ';
        record_condition_2 = (col == 0);

        if (record_condition_1 || record_condition_2) {
            if (intermediary_prints) {
                printf("operator: %c - ", placeholder_operator);
                printf("%lld %lld %lld %lld\n", placeholder_number_array[0], placeholder_number_array[1], placeholder_number_array[2], placeholder_number_array[3]);
            }
            // Initializes the intermediary accumulator
            if (placeholder_operator == '*') {
                temp_acc = 1;
            } else {
                temp_acc = 0;
            }
            // Accumulates
            for (int row = 0; row < row_count-1; row++) {
                if (placeholder_operator == '*') {
                    temp_acc *= placeholder_number_array[row];
                } else if (placeholder_operator == '+') {
                    temp_acc += placeholder_number_array[row];
                } else {
                    perror("Operator not read properly.\n");
                }
            }
            // Records into main accumulator
            accumulator += temp_acc;
            if (intermediary_prints) {
                printf("Temp acc: %lld, total acc: %lld\n", temp_acc, accumulator);
            }
            // Reinitializes intermediary variables
            for (int i = 0; i < row_count-1; i++) {
                placeholder_number_array[i] = 0;
                placeholder_multiplier_array[i] = 1;
                printf("reinit: %lld %lld ", placeholder_number_array[i], placeholder_multiplier_array[i]);
            }
            placeholder_operator = ' ';
        }
    } 

    return accumulator;
}

int main() {
    char * filename = "data.txt";
    int intermediary_prints = 0;
    char array[MAX_ROWS][MAX_COLUMNS] = { 0 };
    
    int row_count = read_file(filename, array);

    // cleans rows
    for (int i = 0; i < row_count; i++) {
        strip_lf(array[i]);
    }

    // finds max search range for columns
    int col_count = find_shortest_row(array, row_count);
    printf("Searchable row length: %d; column length: %d\n", row_count, col_count);

    // tests print
    if (strcmp(filename, "test.txt") == 0){
        intermediary_prints = 1;
        for (int i = 0; i < row_count; i++) {
            for (int j = 0; j < col_count; j++) {
                printf("%c", array[i][j]);
            }
            printf("\n");
        }
    }

    // solves part 1
    long long part_1_result = solve_part1(array, row_count, col_count, intermediary_prints);
    printf("Day 6 Part 1: %lld\n", part_1_result);
}