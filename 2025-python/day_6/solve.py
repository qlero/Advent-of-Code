with open("data.txt", "r") as f:
    x = [' '.join(i.split()).split(" ") for i in f.readlines()]
    x = [[ii.strip() for ii in i] for i in x]
    x[:-1] = [list(map(int, i)) for i in x[:-1]]

accumulators = []

# Part 1

for column in range(len(x[0])):
    accumulator = 1 if x[-1][column] == "*" else 0
    for row in range(len(x[:-1])):
        if x[-1][column] == "*":
            accumulator *= int(x[row][column])
        elif x[-1][column] == "+":
            accumulator += int(x[row][column])
        else: 
            raise ValueError("Wrong operator.")
    accumulators.append(accumulator)

print("Day 6 Part 1: ", sum(accumulators))

# Part 2

with open("data.txt", "r") as f:
    x = [i.replace("\n", "") for i in f.readlines()]
    operators, values = x[-1], x[:-1]
    operators = [ii[0] for ii in [i.split() for i in operators] if ii != []]

current_operator_index = 0
accumulator = 0 if operators[current_operator_index] == "+" else 1
sum_acc = 0

for column in range(len(values[0])):
    multiplier = 1
    temp_value = 0
    check_empty_col = 0
    for row in range(len(values))[::-1]:
        if values[row][column] != ' ':
            check_empty_col += 1
            temp_value += int(values[row][column]) * multiplier
            multiplier *= 10
    if check_empty_col and operators[current_operator_index] == "+":
        accumulator += temp_value
    elif check_empty_col and operators[current_operator_index] == "*":
        accumulator *= temp_value
    if check_empty_col == 0:
        current_operator_index += 1
        sum_acc += accumulator
        accumulator = 0 if operators[current_operator_index] == "+" else 1
    check_empty_col = 0
sum_acc += accumulator

print("Day 6 part 2: ", sum_acc)