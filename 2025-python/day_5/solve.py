with open("test.txt", "r") as f:
    x = [l.strip() for l in f]

blank_space_index = x.index('')
# generates list of fresh elements
range_ids = [list(map(int, l.split("-"))) for l in x[:blank_space_index]]
# elements to check
available = list(map(int, x[blank_space_index+1:]))

# check elements
count = 0
for item in available:
    for rng in range_ids:
        if item >= rng[0] and item <= rng[1]:
            count += 1
            break
print("[v1] Day 5 part 1: ", count)

# Version 1

range_acc  = []
range_ids  = sorted(range_ids)
position   = 0
look_ahead = 1

while position < len(range_ids) and position + look_ahead < len(range_ids):

    # 340433326438191

    if look_ahead == 1:
        placeholder = range_ids[position]

    b = placeholder[1]
    c = range_ids[position + look_ahead][0]
    d = range_ids[position + look_ahead][1]

    if b < c:
        range_acc.append(placeholder)
        position  += look_ahead
        look_ahead = 1
    else:
        placeholder[1] = d if d > placeholder[1] else placeholder[1]
        look_ahead    += 1

else:

    if look_ahead == 1:
        range_acc.append(range_ids[-1])
    else:
        range_acc.append(placeholder)

count = [i[1]-i[0]+1 for i in range_acc]
count = sum(count)

print("[v1] Day 5 part 2: ", count)

# Version 2

range_ids  = sorted(range_ids, key=lambda x: x[0])
count      = 0
position   = 0
look_ahead = 1

while position < len(range_ids) and position + look_ahead < len(range_ids):

    # 340433326438191
    # 343089604671743
    # 355343555459210
    # 350513176552950
    
    if look_ahead == 1:
        placeholder = range_ids[position]

    b = placeholder[1]
    c = range_ids[position + look_ahead][0]
    d = range_ids[position + look_ahead][1]

    if b < c:
        count     += b - placeholder[0] + 1
        position  += look_ahead
        look_ahead = 1
    else:
        placeholder[1] = d if d > placeholder[1] else placeholder[1]
        look_ahead    += 1
else:
    if look_ahead == 1:
        count += range_ids[-1][1] - range_ids[-1][0] + 1
    else:
        count += placeholder[1] - placeholder[0] + 1

print("[v2] Day 5 part 2: ", count)