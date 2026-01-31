with open("data.txt", "r") as f:
    data = [list(map(int,l.strip().split(","))) for l in f.readlines()]

areas = []

print(len(data))

def area(p1, p2):
    return (abs(p2[0]-p1[0])+1) * (abs(p2[1]-p1[1])+1)

for row in range(len(data)):
    for col in range(len(data)):
        areas.append([area(data[row], data[col]), row, col])

result = sorted(areas, key=lambda x:x[0], reverse=True)[0]
print(result)
print("Day 9 part 1: ", result[0], data[result[1]], data[result[2]])
# 4775962256