#include <stdio.h>
#include <string.h>

#include "readfile.h"


int solver_part_1(struct ROW_COUNTS row_counts, long fresh_ids[MAX_ROWS][MAX_COLUMNS], long ids_to_check[MAX_ROWS]) {
    int count = 0;
    for (int i = 0; i < row_counts.row_count_ids_to_check; i++) {
        for (int j = 0; j < row_counts.row_count_fresh_ids; j++) {
            if (ids_to_check[i] >= fresh_ids[j][0] && ids_to_check[i] <= fresh_ids[j][1]){
                count++;
                break;
            }
        }
    }
    return count;
}


int main() {
    
    char * filename = "test.txt";
    long fresh_ids[MAX_ROWS][MAX_COLUMNS] = { 0 };
    long ids_to_check[MAX_ROWS] = { 0 };

    // 1. reads file
    struct ROW_COUNTS row_counts = read_file(filename, fresh_ids, ids_to_check);
    printf("Counted elements -- fresh id ranges: %d; ids to check: %d\n", row_counts.row_count_fresh_ids, row_counts.row_count_ids_to_check);

    // 2. prints arrays if test
    if (strcmp(filename, "test.txt") == 0) {
        printf("Fresh ids:\n");
        for (int i = 0; i < row_counts.row_count_fresh_ids; i++) {
            printf("%ld-%ld\n", fresh_ids[i][0], fresh_ids[i][1]);
        }
        printf("\nFresh ids:\n");
        for (int i = 0; i < row_counts.row_count_ids_to_check; i++) {
            printf("%ld\n", ids_to_check[i]);
        }
    }

    // 3. Solver part 1
    int part1_result = solver_part_1(row_counts, fresh_ids, ids_to_check);
    printf("Day 5 Part 1: %d\n", part1_result);

    return 0;

}