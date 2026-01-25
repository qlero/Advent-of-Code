#include <limits.h>
#include <string.h>
#include <math.h>

#include "readfile.h"

#define MAX_ELEMENTS 10

int find_shortest_row(char array[MAX_ROWS][MAX_COLUMNS], int row_count);
long solve_part1(char array[MAX_ROWS][MAX_COLUMNS], int row_count, int col_count, int intermediary_prints);

long solve_part2(char array[MAX_ROWS][MAX_COLUMNS], int row_count, int col_count, int intermediary_prints){

    // declares placeholder variables
    int check_value, record_condition_1, record_condition_2;
    int array_index = 0;

    long placeholder_number_array[MAX_ELEMENTS];
    long multiplier, temp_acc;

    long accumulator = 0;
    long return_value = 0;
    
    char placeholder_operator = ' ';

    // Initializes arrays
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        placeholder_number_array[i] = 0;
    }

    // backtrack logic
    for (int col = col_count-1; col >= 0; col--){

        // Sets placeholder values
        temp_acc = 0;
        
        // Sets the multiplier
        multiplier = 1;
        check_value = 0;

        for (int row = 0; row < row_count-1; row++) {
            if (array[row][col] != ' '){
                multiplier *= 10;
            }
        } 
        if (multiplier > 1) {
            multiplier /= 10;
        }

        // Iterates over a column
        for (int row = 0; row < row_count-1; row++) {
            if (array[row][col] != ' ') {
                temp_acc += multiplier * (array[row][col]-'0');
                multiplier /= 10;
            } else {
                check_value++;
            }
        }

        // checks for an operator
        if (array[row_count-1][col] != ' ') {
            placeholder_operator = array[row_count-1][col];
        }

        // records the value
        if (check_value != row_count-1){
            placeholder_number_array[array_index] = temp_acc;
            array_index++;
        }

        // Performs accumulation
        record_condition_1 = (check_value == row_count-1) && placeholder_operator != ' ';
        record_condition_2 = (col == 0);

        if (record_condition_1 || record_condition_2) {

            if (intermediary_prints) {
                printf("operator: %c - ", placeholder_operator);
            }

            // Initializes the intermediary accumulator
            if (placeholder_operator == '*') {
                accumulator = 1;
            } else {
                accumulator = 0;
            }

            // Accumulates
            for (int element = 0; element < array_index; element++) {
                if (placeholder_operator == '*') {
                    accumulator *= placeholder_number_array[element];
                } else if (placeholder_operator == '+') {
                    accumulator += placeholder_number_array[element];
                } else {
                    perror("Operator not read properly.\n");
                }
            }
            if (intermediary_prints) {
                printf("Total acc: %ld\n", accumulator);
            }

            // Records accumulated value
            return_value += accumulator;

            // Reinitializes intermediary variables
            for (int i = 0; i < MAX_ELEMENTS; i++) {
                placeholder_number_array[i] = 0;
            }
            placeholder_operator = ' ';
            array_index = 0;
        }
    } 

    return return_value;
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
    long part_1_result = solve_part1(array, row_count, col_count, intermediary_prints);
    printf("Day 6 Part 1: %ld\n", part_1_result);

    // solves part 2
    long part_2_result = solve_part2(array, row_count, col_count, intermediary_prints);
    printf("Day 6 Part 2: %ld\n", part_2_result);
}

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

long solve_part1(char array[MAX_ROWS][MAX_COLUMNS], int row_count, int col_count, int intermediary_prints){

    // declares placeholder variables
    int blank_array_location_check, record_condition_1, record_condition_2;

    long placeholder_number_array[row_count-1];
    long placeholder_multiplier_array[row_count-1];
    long temp_acc;
    long accumulator = 0;

    char placeholder_operator = ' ';

    // Initializes arrays
    for (int i = 0; i < row_count-1; i++) {
        placeholder_number_array[i] = 0;
        placeholder_multiplier_array[i] = 1;
    }

    

    // backtrack logic
    for (int col = col_count-1; col >= 0; col--){

        // Resets placeholder variables
        blank_array_location_check = 0;

        // Iterates over a rows
        for (int row = 0; row < row_count-1; row++) {
            // Increments counter if location empty

            if (array[row][col] == ' ') {
                blank_array_location_check++;
            } else {
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
        }
        
        // Performs accumulation
        record_condition_1 = blank_array_location_check == row_count-1 && array[row_count-1][col] == ' ';
        record_condition_2 = (col == 0);

        if (record_condition_1 || record_condition_2) {

            if (intermediary_prints) {
                printf("operator: %c - ", placeholder_operator);
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
                printf("Temp acc: %ld, total acc: %ld\n", temp_acc, accumulator);
            }

            // Reinitializes intermediary variables
            for (int i = 0; i < row_count-1; i++) {
                placeholder_number_array[i] = 0;
                placeholder_multiplier_array[i] = 1;
            }
            placeholder_operator = ' ';

        }
    } 

    return accumulator;
}