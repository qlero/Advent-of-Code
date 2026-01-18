#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 5000
#define MAX_COLUMNS 2

struct ROW_COUNTS {
    int row_count_fresh_ids;
    int row_count_ids_to_check;
};

struct ROW_COUNTS read_file(char * filename, long fresh_ids[MAX_ROWS][MAX_COLUMNS], long ids_to_check[MAX_ROWS]) {

    FILE * file;
    struct ROW_COUNTS row_counts = {0, 0};

    // 1. open the file in reading mode
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file.");
        row_counts.row_count_fresh_ids = -1;
        row_counts.row_count_ids_to_check = -1;
        return row_counts;
    }

    // 2. read the file to import the fresh IDs
    // fscanf return the number of items successfully read.
    while (fscanf(file, "%ld-%ld", &fresh_ids[row_counts.row_count_fresh_ids][0], &fresh_ids[row_counts.row_count_fresh_ids][1]) == 2) {

        // increments the row count
        row_counts.row_count_fresh_ids++;

        // errors out if issue found
        if (row_counts.row_count_fresh_ids >= MAX_ROWS) {
            perror("Data to be read larger than provided array size.\nRemaining data discarded.");
            break;
        }
    }

    // 2. decrement the file pointer enough [DISGUSTING]
    fseek(file, -sizeof(long), SEEK_CUR);
    int discard_first_find = 1;

    // 3. read the file
    // fscanf return the number of items successfully read.
    while (fscanf(file, "%ld\n", &ids_to_check[row_counts.row_count_ids_to_check]) != EOF) {
        if (discard_first_find) {
            discard_first_find = 0;
            continue;
        }
        // increments the row count
        row_counts.row_count_ids_to_check++;
        // errors out if issue found
        if (row_counts.row_count_ids_to_check >= MAX_ROWS) {
            perror("Data to be read larger than provided array size.\nRemaining data discarded.");
            break;
        }
    }

    fclose(file);

    return row_counts;
}