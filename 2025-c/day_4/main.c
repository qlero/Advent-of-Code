#include <math.h>
#include <stdio.h>
#include <string.h> 

#include "read_file.h"

struct SOLVER_RETURN {
    char array[MAX_ROWS][MAX_COLUMNS];
    int accumulator;
};

struct SOLVER_RETURN solver(struct SOLVER_RETURN state, int radius, int max, int row_count);

struct SOLVER_RETURN_V2 {
    char *array[MAX_COLUMNS];
    int accumulator;
};

struct SOLVER_RETURN_V2 solver_v2(char data[MAX_COLUMNS], int radius, int max, int row_count);


int main() {

    // 1. Create data placeholder and load file content
    char data[MAX_ROWS][MAX_COLUMNS] = {0};
    int row_count = read_file("data.txt", data);
    printf("Found %d datapoints.\n", row_count);

    struct SOLVER_RETURN ret;
    ret.accumulator = 0;
    memcpy(ret.array, data, sizeof(ret.array));

    struct SOLVER_RETURN_V2 ret2 = {data, 0};

    printf("[[Test 1, struct v1] update element 2 of array 0 to '2']\t");
    printf("%s -> ", ret.array[0]);
    ret.array[0][2] = 'a';
    printf("%s\n", ret.array[0]);
    printf("[Test intermediary] check original data array:\t\t\t%s\n", data[0]);
    printf("[[Test 2, struct v1] update accumulator to 2]]\t\t\t");
    printf("%d -> ", ret.accumulator);
    ret.accumulator = 2;
    printf("%d\n", ret.accumulator);
    // reset after test
    // ret.array[0][2] = '@'; # <- NOTE: will break exercise

    printf("[[Test 3, struct v2] update element 2 of array 0 to '2']\t");
    printf("%s -> ", ret2.array[0]);
    ret2.array[0][2] = 'a';
    printf("%s\n", ret2.array[0]);
    printf("[Test intermediary] check original data array:\t\t\t%s\n", data[0]);
    printf("[[Test 4, struct v2] update accumulator to 2]]\t\t\t");
    printf("%d -> ", ret2.accumulator);
    ret2.accumulator = 2;
    printf("%d\n", ret2.accumulator);

    // 2. Solves part 1
    // GT: 1508

    ret = solver(ret, 1, 4, row_count);
    printf("Day 4 Part 1 solution: %d\n", ret.accumulator);

    // 3. Solves part 2
    // GT: 8538
    
    // reinitializes
    ret.accumulator = 0;
    memcpy(ret.array, data, sizeof(ret.array));

    // performs loop
    int sum_accumulator = 0;
    do {
        ret = solver(ret, 1, 4, row_count);
        sum_accumulator += ret.accumulator;
    } while (ret.accumulator != 0);
    printf("Day 4 Part 2 solution: %d\n", sum_accumulator);

    return 0;
}

struct SOLVER_RETURN solver(struct SOLVER_RETURN initial_state, int radius, int max, int row_count) {

    // Creates a copy of the initial state for return
    // Probably can be done away with
    struct SOLVER_RETURN return_state;
    return_state.accumulator = 0;
    memcpy(return_state.array, initial_state.array, sizeof(initial_state.array));
    
    // Declares important temp values
    int array_len = strlen(initial_state.array[0]);

    // iterates over data array in a nested loop as such:
    for (int row = 0; row < row_count; row++) {
        for (int column = 0; column < array_len; column++){
            int occurences = 0;
            // iterates in a ball around the current position
            for (int r_row = row - radius; r_row <= row + radius; r_row++){
                if (occurences > max || r_row < 0 || r_row >= row_count) {
                    continue;
                }
                for (int r_col = column - radius; r_col <= column + radius; r_col++){
                    if (occurences > max || (r_col < 0 || r_col >= array_len) || (r_row == row && r_col == column)) {
                        continue;
                    }
                    if (initial_state.array[r_row][r_col] == '@') {
                        occurences++;
                    }
                } 
            }
            if (occurences < max && return_state.array[row][column] == '@') {
                return_state.array[row][column] = '.';
                return_state.accumulator++;
            }
        }
    }
    return return_state;

}