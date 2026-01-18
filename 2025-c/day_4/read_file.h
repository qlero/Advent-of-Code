#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 500
#define MAX_COLUMNS 200

int read_file(char * filename, char array[MAX_ROWS][MAX_COLUMNS]) {

    FILE * file;
    int row_count = 0;

    // 1. open the file in reading mode
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file.");
        return -1;
    }

    // 2. read the file
    // fscanf return the number of items successfully read.
    while (fscanf(file, "%s\n", &array[row_count][0]) == 1) {

        // increments the row count
        row_count++;

        // errors out if issue found
        if (row_count >= MAX_ROWS) {
            perror("Data to be read larger than provided array size.\nRemaining data discarded.");
            break;
        }
    }

    fclose(file);

    return row_count;
}