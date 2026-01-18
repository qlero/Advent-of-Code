#include <math.h>
#include <stdio.h>
#include <string.h> 

#include "read_file.h"

long solver(char data[MAX_COLUMNS], int size);

int main() {

    // 1. Create data placeholder and load file content
    char data[MAX_ROWS][MAX_COLUMNS] = {0};
    int row_count = read_file("data.txt", data);
    printf("Found %d datapoints.\n", row_count);

    long accumulator = 0;

    // 2. Solves part 1
    // GT: 16946

    for (int i = 0; i < row_count; i++) {
        accumulator += solver(data[i], 2);
    }
    printf("Day 3 part 1 Solution: %ld\n", accumulator);
    
    // 3. Solves part 2
    // GT: 168627047606506

    accumulator = 0;
    for (int i = 0; i < row_count; i++) {
        accumulator += solver(data[i], 12);
    }
    printf("Day 3 part 2 Solution: %ld\n", accumulator);

    return 0;
}

long solver(char data[MAX_COLUMNS], int size) {

    // Declares important temp values

    long accumulator = 0;
    long digit_place = pow(10, size-1); 
    
    int index        = 0;
    int temp_index   = 0;

    // iterates over data array in a nested loop as such:
    // 1. Iterates over size to exclude <curr_size> elements from the search
    // 2. Finds the maximum value and its index in the data array
    //    between <index> and <curr_size>
    // 3. Updates the accumulator
    for (int i = size-1; i >= 0; i--){
        int max_value = 0;
        for (int j = index; j < strlen(data)-i; j++) {
            int current_value = data[j] - '0';
            // Finds the max value and updates the search's start index
            if (current_value > max_value) {
                max_value  = current_value;
                temp_index = j;
            }
        }
        // Updates the accumulator
        accumulator += max_value * digit_place;
        index        = temp_index + 1; 
        digit_place /= 10;
    }
    
    return accumulator;

}