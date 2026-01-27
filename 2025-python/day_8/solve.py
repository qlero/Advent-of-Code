"""
162,817,812
57,618,57
906,360,560
592,479,940
352,342,300
466,668,158
542,29,236
431,825,988
739,650,466
52,470,668
216,146,977
819,987,18
117,168,530
805,96,715
346,949,466
970,615,88
941,993,340
862,61,35
984,92,344
425,690,689

> straight-line distance

1. 162,817,812 and 425,690,689 -> 1 two-box circuit, 18 one-box circuits
2. 162,817,812 and 431,825,988 -> 1 three-box circuit, 17 one-box circuits
3. 906,360,560 and 805,96,715  -> 1 three-box circuit, 1 two-box circuit, 15 one-box circuits
4. 431,825,988 and 425,690,689 -> nothing happens!

end. 11 circuits: 1 five-box circuit, 1 four-box circuit, 2 two-box circuits, 7 one-box circuits

res. Multiplying together the sizes of the **three** largest circuits (5 * 4 * 2) -> 40.

goal. (1) connect together the 1000 pairs of junction boxes which are closest together
      (2) multiply together the sizes of the **three** largest circuits?
"""

import math

def euclidean_distance(p1, p2):
    return math.sqrt((p2[0]-p1[0])**2 + (p2[1]-p1[1])**2 + (p2[2]-p1[2])**2)

def solver(data, max_connections=None):
    # Stricly upper triangular "matrix" of euclidean distance between points
    sutm_dist_between_points = [[euclidean_distance(p1, p2) for p2 in data[i+1:]] for i, p1 in enumerate(data[:-1])]
    # Placeholder for the current connection of each point (each point has its own cluster)
    cluster_of_each_point = list(range(len(sutm_dist_between_points)+1))
    # Placeholder for the size of each cluster
    size_of_each_cluster = [1 for _ in range(len(sutm_dist_between_points)+1)]
    # Placeholder for checking if mapped
    check_mapping_point = [False for _ in range(len(sutm_dist_between_points)+1)]

    # Finds the initial minimum distances
    min_values  = [min(l) for l in sutm_dist_between_points]
    min_value   = min(min_values)

    print_test = False if max_connections is None else max_connections < 20

    # Starts iteration
    while sum([l != 0 for l in size_of_each_cluster])!=1 if (max_connections is None) else max_connections > 0:

        # Finds the array location of p1 and p2 (the closest point at the time)
        index_p1          = min_values.index(min_value)
        relative_index_p2 = sutm_dist_between_points[index_p1].index(min_value)
        index_p2          = relative_index_p2 + index_p1 + 1

        # Case 1: p1 and p2 are singletons to be joined -> join p2 to p1 cluster
        #         p1 is in a cluster but not p2
        if ((not check_mapping_point[index_p1]) and (not check_mapping_point[index_p2])):

            # Updates p2 cluster and decrement previous p2 cluster size
            cluster_of_each_point[index_p2] = cluster_of_each_point[index_p1]
            size_of_each_cluster[index_p2] -= 1

            # Updates p1 cluster size
            size_of_each_cluster[index_p1] += 1
            
            # Updates check
            check_mapping_point[index_p1] = True
            check_mapping_point[index_p2] = True

        # Case 2: p1 is not in a cluster but p2 is -> join p1 to p2 cluster
        elif check_mapping_point[index_p1] and (not check_mapping_point[index_p2]):

            # Updates cluster sizes
            size_of_each_cluster[index_p2] -= 1
            size_of_each_cluster[cluster_of_each_point[index_p1]] += 1

            # Updates p2 cluster and decrement previous p2 cluster size
            cluster_of_each_point[index_p2] = cluster_of_each_point[index_p1]
            
            # Updates check
            check_mapping_point[index_p2] = True

        # Case 3: p1 is not in a cluster but p2 is -> join p1 to p2 cluster
        elif (not check_mapping_point[index_p1]) and check_mapping_point[index_p2]:

            # Updates cluster sizes
            size_of_each_cluster[index_p1] -= 1
            size_of_each_cluster[cluster_of_each_point[index_p2]] += 1

            # Updates p1 cluster and decrement previous p1 cluster size
            cluster_of_each_point[index_p1] = cluster_of_each_point[index_p2]
            
            # Updates check
            check_mapping_point[index_p1] = True

        # Case 4: p1 and p2 are on 2 different clusters -> merge
        elif (check_mapping_point[index_p1] and check_mapping_point[index_p2]) and \
            cluster_of_each_point[index_p1] != cluster_of_each_point[index_p2]:
            
            receiving_cluster = cluster_of_each_point[index_p1]
            giving_cluster = cluster_of_each_point[index_p2]

            for i in range(len(cluster_of_each_point)):
                if cluster_of_each_point[i] == giving_cluster:
                    size_of_each_cluster[receiving_cluster] += 1
                    size_of_each_cluster[giving_cluster] -= 1
                    cluster_of_each_point[i] = receiving_cluster

        # Case 5: p1 and p2 are already mapped on the same cluster -> else nothing happens
        # else:
        #     print("case 5: nothing happens", data[index_p1], data[index_p2])

        if max_connections is not None:
            max_connections -= 1
        
        sutm_dist_between_points[index_p1][relative_index_p2] = float("inf")
        
        min_values  = [min(l) for l in sutm_dist_between_points]
        min_value   = min(min_values)

    if print_test:
        print("Nb. circuits: ", sum([1 if l!=0 else 0 for l in size_of_each_cluster]))
        for i in range(len(cluster_of_each_point)):
            print(f"Cluster {i} nb. elements: {size_of_each_cluster[i]}")
    
    if max_connections is not None:
        print("result: ", math.prod([s for s in sorted(size_of_each_cluster)[-3:] if s!=0]))
    else:
        print("result: ", data[index_p1][0] * data[index_p2][0])

with open("data.txt", "r") as f:
    data = [[int(ll) for ll in l.strip().split(",")] for l in f]

print("Day 8 part 1:")
part_1 = solver(data, 1000)
print("\nDay 8 part 2:")
part_2 = solver(data)