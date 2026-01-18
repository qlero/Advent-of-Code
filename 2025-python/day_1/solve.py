with open("data.txt", "r") as f:
    data = [[line[0], int(line[1:])] for line in f]
dial = [n for n in range(0, 100)]

def left(index):
    return dial[index-1]

def right(index):
    return dial[(index+1) % 100]

def part2():
    index = 50
    total = 0
    for turn in data: 
        if turn[0] == 'L':
            for _ in range(turn[1]):
                index = left(index)
                if index == 0:
                    total += 1
        else:
            for _ in range(turn[1]):
                index = right(index)
                if index == 0:
                    total += 1
    return total

print(part2())