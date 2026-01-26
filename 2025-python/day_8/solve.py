import math

def euclidean_distance(p1, p2):
    return math.sqrt((p2[0]-p1[0])**2 + (p2[1]-p1[1])**2 + (p2[2]-p1[2])**2)

with open("test.txt", "r") as f:
    data = [[int(ll) for ll in l.strip().split(",")] for l in f]

distances      = [[euclidean_distance(p1, p2) for p2 in data[i+1:]] for i, p1 in enumerate(data[:-1])]
graph_clusters = [-float("inf") for _ in range(len(data))]
current_cluster = -1
size_clusters = {k:1 for k in range(len(distances)+1)}

min_values  = [min(l) for l in distances]
min_value   = min(min_values)

while min_value != float("inf"):
    
    check = sum([l == -float("inf") for l in graph_clusters])
    if check == 0:
        break

    start_point   = min_values.index(min_value)
    end_point     = distances[start_point].index(min_value)
    print("before:", start_point, data[start_point], end_point, start_point+end_point+1, data[start_point+end_point+1])

    start_cluster = graph_clusters[start_point]
    end_cluster   = graph_clusters[start_point+end_point+1]

    # print(start_point, end_point, start_cluster, end_cluster, graph_clusters)

    if start_cluster == -float("inf") and end_cluster != -float("inf"):

        print("case 1")
        graph_clusters[start_point] = graph_clusters[end_point+start_point+1] 
        size_clusters[end_cluster] += 1
        size_clusters[start_point] -= 1

    elif start_cluster != -float("inf") and end_cluster == -float("inf"):

        print("case 2")
        graph_clusters[end_point+start_point+1] = graph_clusters[start_point] 
        size_clusters[start_cluster] += 1
        size_clusters[start_point+end_point+1] -= 1

    elif start_cluster == -float("inf") and end_cluster == -float("inf"):

        print("case 3")
        current_cluster += 1
        graph_clusters[start_point] = current_cluster
        graph_clusters[end_point+start_point+1] = current_cluster
        size_clusters[current_cluster] += 1
        if current_cluster == start_point:
            size_clusters[start_point+end_point+1] -= 1
        elif current_cluster == start_point+end_point+1:
            size_clusters[start_point] -= 1
        else:
            size_clusters[start_point] -= 1
            size_clusters[start_point+end_point+1] -= 1

    # else nothing happens
    else:
        print("nothing happens")
    
    distances[start_point][end_point] = float("inf")
    
    min_values  = [min(l) for l in distances]
    min_value   = min(min_values)
    
    print("after :", start_point, data[start_point], end_point, start_point+end_point+1, data[start_point+end_point+1])
    print(size_clusters)
    # print(start_point, current_cluster, end_point+start_point+1, data[start_point], data[end_point+start_point+1], min_value, graph_clusters)

# print(graph_clusters)

for i in range(len(graph_clusters)):
    print(f"Cluster {i} nb. elements: {size_clusters[i]}")