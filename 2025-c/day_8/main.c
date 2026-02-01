#include <string.h> 
#include <math.h>

#include "read_file.h"

long euclidean_distance(long coordinate_1[MAX_COLUMNS], long coordinate_2[MAX_COLUMNS]) {
    long dist_x = pow(coordinate_1[0] - coordinate_2[0], 2);
    long dist_y = pow(coordinate_1[1] - coordinate_2[1], 2);
    long dist_z = pow(coordinate_1[2] - coordinate_2[2], 2);
    return sqrt(dist_x + dist_y + dist_z);
}

long solver(long array[MAX_ROWS][MAX_COLUMNS], int max_connections, int row_count) {

    // Initiates and populates strictly upper triangular "matrix" of euclidean distance between two points
    int nb_elements = row_count * (row_count - 1) / 2;
    long sutm_dist_between_points[nb_elements];
    memset(sutm_dist_between_points, 0, nb_elements * sizeof(long));
    int index = 0;
    for (int row = 0; row < row_count-1; row++) { 
        for (int col = row + 1; col < row_count; col++) { 
            sutm_dist_between_points[index] = euclidean_distance(array[row], array[col]);
            index++;
        }
    }

    // placeholder for the current connection of each point (each point has its own cluster)
    int cluster_of_each_point[index];
    for (int i = 0; i < index; i++) {
        cluster_of_each_point[i] = i;
    }

    // placeholder for the current size of each cluster
    int size_of_each_cluster[index];
    memset(cluster_of_each_point, 1, index * sizeof(int));

    // placeholder for checking if the cluster/item has been previously covered
    int check_mapping_point[index];
    memset(check_mapping_point, 0, index * sizeof(int));

    return 1;
}


int main() {

    char * filename = "test.txt";

    long array[MAX_ROWS][MAX_COLUMNS];
    memset(array, 0, MAX_ROWS * MAX_COLUMNS * sizeof(long));
    
    int row_count = read_file(filename, array);
    printf("File read, row count: %d\n", row_count);

    long result_part_1 = solver(array, 1000, row_count);
    printf("Day 8 Part 1: %ld\n", result_part_1);

    return 1;
}