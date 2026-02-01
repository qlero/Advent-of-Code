#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_COLUMNS 500
#define MAX_ROWS 1000

int read_file(char * filename, char array[MAX_ROWS][MAX_COLUMNS]) {

    FILE * file;
    int row_count = 0;

    // opens file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file.");
        return -1;
    }

    while ( fgets ( array[row_count], MAX_COLUMNS , file ) != NULL ){ /* read a line */
        row_count++;
    }


    fclose(file);

    return row_count;
}
