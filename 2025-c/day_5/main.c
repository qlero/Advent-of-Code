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

int compare( const void* a, const void* b) {
    
    // https://stackoverflow.com/questions/3893937/sorting-an-array-in-c

    long int_a = * ( (long*) a );
    long int_b = * ( (long*) b );
     
    if ( int_a == int_b ) {
        return 0;
    } else if ( int_a < int_b ) {
        return -1;
    } else {
        return 1;
    }
}

long solver_part_2(struct ROW_COUNTS row_counts, long fresh_ids[MAX_ROWS][MAX_COLUMNS]) {

    // placeholder variables
    long count     = 0;
    int position   = 0;
    int look_ahead = 1;

    long placeholder_start, placeholder_end;
    long b, c, d;

    qsort(fresh_ids, row_counts.row_count_fresh_ids, sizeof(fresh_ids[0]), compare);

    while (position < row_counts.row_count_fresh_ids && position + look_ahead < row_counts.row_count_fresh_ids) {

        // Stores checked values into placeholders
        if (look_ahead == 1) {
            placeholder_start = fresh_ids[position][0];
            placeholder_end = fresh_ids[position][1];
        }

        b = placeholder_end;
        c = fresh_ids[position + look_ahead][0];
        d = fresh_ids[position + look_ahead][1];

        //
        if (b < c) {
            count      += b - placeholder_start + 1;
            position   += look_ahead;
            look_ahead  = 1;
        } else {
            placeholder_end = (d > placeholder_end) ? d : placeholder_end;
            look_ahead++;
        }
    }

    if (look_ahead == 1) {
        count += fresh_ids[row_counts.row_count_fresh_ids-1][1] - fresh_ids[row_counts.row_count_fresh_ids-1][0] + 1;
    } else {
        count += placeholder_end - placeholder_start + 1;
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

    // 4. Solver part 2
    long part2_result = solver_part_2(row_counts, fresh_ids);
    printf("Day 5 Part 2: %ld\n", part2_result);

    return 0;

}