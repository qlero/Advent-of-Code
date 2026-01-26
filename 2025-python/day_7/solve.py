with open("data.txt", "r") as f:
    data = [l.strip() for l in f.readlines()]

count_splits = 0

for row in range(1, len(data)):

    above_row   = list(data[row-1])
    current_row = list(data[row])

    for col in range(len(data[0])):

        above   = above_row[col]
        current = current_row[col]

        if above == 'S':
            current_row[col] = '|'

        elif above == '|':

            if current == '^':

                if col-1>=0 and current_row[col-1]!='^':
                    current_row[col-1] = '|'

                if col+1<len(data[0]) and current_row[col+1]!='^':
                    current_row[col+1] = '|'

                count_splits += 1
            
            else:

                current_row[col] = '|'

    current_row = ''.join(current_row)
    data[row] = current_row

print("Day 7 part 1: ", count_splits)


with open("data.txt", "r") as f:
    data = [l.strip() for l in f.readlines()]

count_splits = 0
memory_timelines = [0 for _ in range(len(data[0]))]

for row in range(1, len(data)):

    above_row   = list(data[row-1])
    current_row = list(data[row])

    for col in range(len(data[0])):

        above   = above_row[col]
        current = current_row[col]

        if above == 'S':
            current_row[col] = '|'
            memory_timelines[col] = 1
            break

        elif above == '|':

            if current == '^':

                if col-1>=0 and current_row[col-1]!='^':
                    current_row[col-1] = '|'
                    memory_timelines[col-1] += memory_timelines[col]

                if col+1<len(data[0]) and current_row[col+1]!='^':
                    current_row[col+1] = '|'
                    memory_timelines[col+1] += memory_timelines[col]
                
                memory_timelines[col] = 0
                count_splits += 1
            
            else:

                current_row[col] = '|'

    current_row = ''.join(current_row)
    data[row] = current_row

print("Day 7 part 2: ", sum(memory_timelines))