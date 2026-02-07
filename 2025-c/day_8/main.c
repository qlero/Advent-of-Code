#include <string.h> 
#include <math.h>
#include <limits.h>

#include "read_file.h"

struct relative_indexes {
    int index_p1;
    int index_p2;
};

long euclidean_distance(long coordinate_1[MAX_COLUMNS], long coordinate_2[MAX_COLUMNS]) {
    long dist_x = pow(coordinate_1[0] - coordinate_2[0], 2);
    long dist_y = pow(coordinate_1[1] - coordinate_2[1], 2);
    long dist_z = pow(coordinate_1[2] - coordinate_2[2], 2);
    return sqrt(dist_x + dist_y + dist_z);
}

struct relative_indexes compute_relative_indexes(long array[], int length_array, int nb_elements, long a[MAX_ROWS][MAX_COLUMNS]) {
    long minimum = LONG_MAX;

    int temp_p1 = 0;
    int index_p1 = 0;
    int index_p2 = 0;

    printf("%d\n", length_array);

    int check_value = nb_elements - 1;
    int increment_check_value = check_value - 1;
    int decrement_index_p2 = 0;

    printf("%d\n", length_array);

    for (int i = 0; i < length_array; i++){
        if (array[i] < minimum) {
            minimum = array[i];
            index_p1 = temp_p1;
            index_p2 = i - decrement_index_p2;
        }
        if (i >= check_value) {
            temp_p1++;
            decrement_index_p2 = check_value;
            check_value += increment_check_value;
            increment_check_value--;
            // printf("%d\n", decrement_index_p2);
        }
        printf("%d - %d | %d %d | %d %d ||| ", i, temp_p1, index_p1, index_p2, check_value, increment_check_value);
        printf("(%ld,%ld,%ld) (%ld, %ld,%ld)\n", 
        a[index_p1][0],
        a[index_p1][1],
        a[index_p1][2],
        a[index_p2][0],
        a[index_p2][1],
        a[index_p2][2]);
    }

    struct relative_indexes ret = {index_p1, index_p2};
    return ret;
}



long solver(long array[MAX_ROWS][MAX_COLUMNS], int max_connections, int row_count) {

    // Initiates and populates strictly upper triangular "matrix" of euclidean distance between two points
    int length_upper_triangle_matrix_as_vector = row_count * (row_count - 1) / 2;
    long sutm_dist_between_points[length_upper_triangle_matrix_as_vector];
    memset(sutm_dist_between_points, 0, length_upper_triangle_matrix_as_vector * sizeof(long));
    int index = 0;
    for (int row = 0; row < row_count-1; row++) { 
        for (int col = row + 1; col < row_count; col++) { 
            sutm_dist_between_points[index] = euclidean_distance(array[row], array[col]);
            index++;
        }
    }

    // placeholder for the current connection of each point (each point has its own cluster)
    int cluster_of_each_point[row_count];
    for (int i = 0; i < row_count; i++) {
        cluster_of_each_point[i] = i;
    }

    // placeholder for the current size of each cluster
    int size_of_each_cluster[row_count];
    memset(cluster_of_each_point, 1, row_count * sizeof(int));

    // placeholder for checking if the cluster/item has been previously covered
    int check_mapping_point[row_count];
    memset(check_mapping_point, 0, row_count * sizeof(int));

    // Finds the initial minimum distances
    struct relative_indexes indexes = compute_relative_indexes(sutm_dist_between_points, length_upper_triangle_matrix_as_vector, row_count, array);
    printf("%d %d\n", indexes.index_p1, indexes.index_p2);

    printf("(%ld,%ld,%ld) (%ld, %ld,%ld)\n", 
        array[indexes.index_p1][0],
        array[indexes.index_p1][1],
        array[indexes.index_p1][2],
        array[indexes.index_p2][0],
        array[indexes.index_p2][1],
        array[indexes.index_p2][2]);

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