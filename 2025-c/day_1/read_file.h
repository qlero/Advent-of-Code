#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 10000 // Maximum number of lines we expect

long day_1_read_file(char * filename, char * rotations, int * distances) {

    FILE *file;

    long row_count = 0;

    // 1. Open the file for reading ("r")
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    // 2. Read the file
    // fscanf returns the number of items successfully read.
    // We expect 2 items per loop iteration.
    // We also check row_count to prevent writing outside the array memory.
    while (fscanf(file, "%c%d\n", &rotations[row_count], &distances[row_count]) == 2) {
        
        row_count++;
        
        // Safety check to avoid Buffer Overflow
        if (row_count >= MAX_ROWS) {
            printf("Warning: Array full, stopped reading early.\n");
            break;
        }
    }

    // 3. Close the file
    fclose(file);

    return row_count;
}