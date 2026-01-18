
def read_file(filename):
    with open(filename, "r") as f:
        data = [l.split(",") for l in f.readlines()][0]
        data = [l.split("-") for l in data]
        data = [list(range(int(l[0]), int(l[1])+1)) for l in data]
    return data

# PART 1 #

def part_1(filename):
    # reads
    data = read_file(filename)
    # unwraps
    data = [str(ll) for l in data for ll in l]
    # removes elements with non-even number of digits
    data = [l for l in data if len(l)%2==0]
    mask = [l[:len(l)//2] == l[len(l)//2:] for l in data]
    data = [int(l) for i,l in enumerate(data) if mask[i]]
    return sum(data)


# PART 2 #

def part_2(filename):
    # reads
    data = read_file(filename)
    # unwraps
    data = [str(ll) for l in data for ll in l]
    # removes elements with non-even number of digits
    mask = [True for _ in range(len(data))]
    # identifies bad IDs
    for i, d in enumerate(data):
        for l in range(1, len(d)//2+1):
            if round(len(d)/len(d[:l]), 0) != len(d)/len(d[:l]):
                continue
            if d.count(d[:l]) == len(d)//l:
                mask[i] = False
                break 
    data = [int(l) for i,l in enumerate(data) if not mask[i]]
    return sum(data)

if __name__ == "__main__":

    filename = "data.txt"

    print("Day 2, part 1 solution: ", part_1(filename))

    print("Day 2, part 2 solution: ", part_2(filename))