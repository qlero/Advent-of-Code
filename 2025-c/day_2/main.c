#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_file.h"

int main() 
{
    // declares the target filename
    char * filename = "data.txt";

    // declares the rotation and distance arrays
    long start[MAX_ELEMENTS]; 
    long end[MAX_ELEMENTS]; 
    
    long cutoff;
    long sum;

    long read_lines;
    
    int check;

    char buffer[16] = {0};

    // loads file
    read_lines = day_2_read_file(filename, start, end);
    if (read_lines == -1) 
    {
        return 1;
    }
    printf("Number of lines read: %ld\n", read_lines);

    /*
    The ranges are separated by commas (,).
    Each range gives its first ID and last ID separated by a dash (-).
    
    You can find the invalid IDs by looking for any ID which is made only of some sequence of digits repeated twice. 
    So:
        - 55 (5 twice),
        - 6464 (64 twice),
        - and 123123 (123 twice) would all be invalid IDs.

    None of the numbers have leading zeroes; 0101 isn't an ID at all. (101 is a valid ID that you would ignore.)
    Your job is to find all of the invalid IDs that appear in the given ranges. In the above example:
    */

    for (long i = 0; i < read_lines; i++) {
        for (long j = start[i]; j <= end[i]; j++) {
            // reads the number into a character array
            sprintf(buffer, "%ld", j);
            // checks the character array for repetitions
            if (strlen(buffer) % 2 == 0){
                cutoff = strlen(buffer) / 2;
                check = 1;
                for (long u = 0; u < cutoff; u++){
                    if (buffer[u] != buffer[u+cutoff]) {
                        check = 0;
                    }
                }
                if (check) {
                    printf("FOUND: %ld\n", j);
                    sum += j;
                }
            }
        }
    }

    printf("Deduced value (day 2, part 1):\t%ld\n", sum);

    /*
    An ID is invalid if it is made only of some sequence of digits repeated at least twice. 
    So, 12341234 (1234 two times), 123123123 (123 three times), 1212121212 (12 five times), and 1111111 (1 seven times) are all invalid IDs.
    */

    sum = 0;

    // loops over existing elements
    for (long i = 0; i < read_lines; i++) {
        for (long j = start[i]; j <= end[i]; j++) {
            // reads the number into a character array
            sprintf(buffer, "%ld", j);
            check = 0;
            // loops over sliding window sizes
            for (long u = 1; u <= strlen(buffer) / 2; u++) {
                // copies initial array
                char *slice_initial = &buffer[0];
                for (long v = u; v <= strlen(buffer); v += u) {
                    // copies amputated array for compare
                    char *slice_to_compare = &buffer[v];
                    // compare the two array over window of size u
                    // breaks out if a fail match is found
                    if (strncmp(slice_initial, slice_to_compare, u) != 0) {
                        break;
                    }
                    // if match found, checks if at end of buffer
                    if (v+u == strlen(buffer)) {
                        check = 1;
                        // breaks out since the rest of the computation is useless
                        break;
                    }
                }
            }
            // Increment if one repeating pattern was found
            if (check) {
                printf("FOUND: %ld\n", j);
                sum += j;
            }
        }
    }

    printf("Deduced value (day 2, part 2):\t%ld\n", sum);

    return 0;
}