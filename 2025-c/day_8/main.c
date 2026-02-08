#include <string.h> 
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "read_file.h"

struct relative_indexes {
    int index_p1;
    int index_p2;
    int relative_index_p2;
};

long euclidean_distance(long coordinate_1[MAX_COLUMNS], long coordinate_2[MAX_COLUMNS]) {
    long dist_x = pow(coordinate_1[0] - coordinate_2[0], 2);
    long dist_y = pow(coordinate_1[1] - coordinate_2[1], 2);
    long dist_z = pow(coordinate_1[2] - coordinate_2[2], 2);
    return sqrt(dist_x + dist_y + dist_z);
}

struct relative_indexes compute_relative_indexes(long flat_array[], int length_array, int nb_elements) {
    /*
    Traverses <flat_array> to find the indexes in <array> (see solver()) of elements with the smallest distance.
    -- args --
    flat_array : one-dimensional array corresponding to a flattened strictly upper-triangle matrix or SUTM
                 (null diagonal) containing the distances between each points in the underlying file
                         1   2   3   ...
                     1   /   a   b   c..
                     2   /   /   d   e.. => [a, b, c, d, e, f, ...]
                     3   /   /   /   f..
                     ...
    length_array : length of <flat_array>.
    nb_elements : number of datapoints in <array> (see solver()).
    */

    // Initializes placeholder and return variables
    long minimum = LONG_MAX;
    int temp_p1 = 0;
    int index_p1 = 0;
    int index_p2 = 1;
    int relative_index_p2 = 1;

    int check_value = nb_elements - 1;
    int increment_check_value = check_value - 1;
    int decrement_index_p2 = 0;

    for (int i = 0; i < length_array; i++){
        // Checks for how many elements have been traversed to see if we
        // swap to a new first datapoint (i.e. corresponding to a new row 
        // in the SUTM underlying <flat_array>).
        if (i >= check_value) {
            // Jumps to new row in SUTM.
            temp_p1++;
            // Updates the decrement value to compute the proper index of 
            // the second datapoint in <array>.
            decrement_index_p2 = check_value;
            check_value       += increment_check_value;
            // The number of distances to be checked decreases in each 
            // row of the SUTM.
            increment_check_value--;
        }
        // if a new smallest distance is found, records the indexes of 
        // underlying the matching points
        if (flat_array[i] <= minimum) {
            minimum  = flat_array[i];
            index_p1 = temp_p1;
            index_p2 = i - decrement_index_p2 + 1*(index_p1+1);
            relative_index_p2 = i;
        }
    }

    struct relative_indexes ret = {index_p1, index_p2, relative_index_p2};
    return ret;
}

int more_than_one_cluster(long * size_of_each_cluster, int row_count) {
    /*
    Checks if only one cluster remains.
    */
    int check = 0;
    for (int i = 0; i < row_count; i++) {
        if (size_of_each_cluster[i] != 0) {
            check++;
        }
        if (check > 1) {
            return 1;
        }
    }
    return 0;
}

int compare( const void* a, const void* b)
{
   long int_a = * ( (long*) a );
   long int_b = * ( (long*) b );

   // an easy expression for comparing
   return (int_a > int_b) - (int_a < int_b);
}

long solver(long array[MAX_ROWS][MAX_COLUMNS], int max_connections, int row_count) {

    // Initiates placeholder struct for return values from compute_relative_indexes
    struct relative_indexes indexes;
    long result_part_1;
    long result_part_2;

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
    long cluster_of_each_point[row_count];
    for (int i = 0; i < row_count; i++) {
        cluster_of_each_point[i] = i;
    }


    // placeholder for the current size of each cluster
    long size_of_each_cluster[row_count];
    // memset(size_of_each_cluster, 1, row_count * sizeof(int));
    for (int i = 0; i < row_count; i++) {
        size_of_each_cluster[i] = 1;
    }

    // placeholder for checking if the cluster/item has been previously covered
    long check_mapping_point[row_count];
    memset(check_mapping_point, 0, row_count * sizeof(long));

    while (max_connections != -1 ? max_connections > 0 : more_than_one_cluster(size_of_each_cluster, row_count)) {
        
        // Prints the current SUTM
        // int u = 0;
        // for (int row = 0; row < row_count-1; row++) { 
        //     for (int i = 0; i < row; i++){
        //         printf("\t");
        //     }
        //     for (int col = row + 1; col < row_count; col++) { 
        //         printf("%ld\t", sutm_dist_between_points[u]);
        //         u++;
        //     }
        //     printf("\n");
        // }

        // Finds the initial array location of p1 and p2 (the closest point at the time)
        indexes = compute_relative_indexes(
            sutm_dist_between_points, 
            length_upper_triangle_matrix_as_vector, 
            row_count
        );

        printf("(%ld,%ld,%ld) (%ld, %ld,%ld) - dist: %ld\n", 
        array[indexes.index_p1][0],
        array[indexes.index_p1][1],
        array[indexes.index_p1][2],
        array[indexes.index_p2][0],
        array[indexes.index_p2][1],
        array[indexes.index_p2][2],
        sutm_dist_between_points[indexes.relative_index_p2]);

        // if (max_connections < 900) {
        // break;
        // }

        // Case 1: p1 and p2 are singletons to be joined -> join p2 to p1 cluster
        //         p1 is in a cluster but not p2
        if ((!check_mapping_point[indexes.index_p1]) && (!check_mapping_point[indexes.index_p2])) {

            printf("Case 1\n");

            // Updates p2 cluster and decrement previous p2 cluster size
            cluster_of_each_point[indexes.index_p2] = cluster_of_each_point[indexes.index_p1];
            size_of_each_cluster[indexes.index_p2]--;
            // Updates p1 cluster size
            size_of_each_cluster[indexes.index_p1]++;
            // Updates check
            check_mapping_point[indexes.index_p1] = 1;
            check_mapping_point[indexes.index_p2] = 1;

        }
        // Case 2: p1 is in a cluster but not p2 -> join p2 to p1 cluster
        else if (check_mapping_point[indexes.index_p1] && (!check_mapping_point[indexes.index_p2])) {

            printf("Case 2\n");
            
            // Updates p2 cluster and decrement previous p2 cluster size
            size_of_each_cluster[indexes.index_p2]--;
            size_of_each_cluster[cluster_of_each_point[indexes.index_p1]]++;
            // Updates p1 cluster size
            cluster_of_each_point[indexes.index_p2] = cluster_of_each_point[indexes.index_p1];
            // Updates check
            check_mapping_point[indexes.index_p2] = 1;

        }
        // Case 3: p2 is in a cluster but not p1 -> join p1 to p2 cluster
        else if ((!check_mapping_point[indexes.index_p1]) && check_mapping_point[indexes.index_p2]) {

            printf("Case 3\n");
            
            // Updates p2 cluster and decrement previous p2 cluster size
            size_of_each_cluster[indexes.index_p1]--;
            size_of_each_cluster[cluster_of_each_point[indexes.index_p2]]++;
            // Updates p1 cluster size
            cluster_of_each_point[indexes.index_p1] = cluster_of_each_point[indexes.index_p2];
            // Updates check
            check_mapping_point[indexes.index_p1] = 1;
            
        }
        // Case 4: p1 and p2 are in two different clusters -> merge
        else if ((check_mapping_point[indexes.index_p1] && check_mapping_point[indexes.index_p2])
                 &&
                 (cluster_of_each_point[indexes.index_p1] != cluster_of_each_point[indexes.index_p2])) {

            printf("Case 4\n");

            for (int i=0; i < row_count; i++) {
                if (cluster_of_each_point[i] == cluster_of_each_point[indexes.index_p2]) {
                    size_of_each_cluster[cluster_of_each_point[indexes.index_p1]]++;
                    size_of_each_cluster[cluster_of_each_point[indexes.index_p2]]--;
                    cluster_of_each_point[i] = cluster_of_each_point[indexes.index_p1];
                }
            }

        }
        // Case 5: p1 and p2 are already mapped on the same cluster -> do nothing
        // else {
        //     printf("Case 5: nothing happens\n");
        // }
        
        if (max_connections >= 0) {
            max_connections--;
        }

        sutm_dist_between_points[indexes.relative_index_p2] = LONG_MAX;
    }

    if (max_connections != -1) {
        // Part 1
        qsort(size_of_each_cluster, row_count, sizeof(long), compare);
        printf("[");
        for (int i = 0; i < row_count; i++) {
            printf("%ld, ", size_of_each_cluster[i]);
        }
        printf("]\n");

        result_part_1 = 1;
        for (int i = row_count-3; i < row_count; i++) {
            printf("%d %ld\n", i, size_of_each_cluster[i]);
            result_part_1 *= size_of_each_cluster[i];
        }
        return result_part_1;
    } 
    else {
        // Part 2
        result_part_2 = array[indexes.index_p1][0] * array[indexes.index_p2][0];
        return result_part_2;
    }

    return 0;
}


int main() {

    char * filename = "data.txt";

    long array[MAX_ROWS][MAX_COLUMNS];
    memset(array, 0, MAX_ROWS * MAX_COLUMNS * sizeof(long));
    
    int row_count = read_file(filename, array);
    printf("File read, row count: %d\n", row_count);

    int result_part_1 = solver(array, 1000, row_count);
    printf("Day 8 Part 1: %d\n", result_part_1);

    // long result_part_2 = solver(array, -1, row_count);
    // printf("Day 8 Part 2: %ld\n", result_part_2);

    return 1;
}