with open("data.txt", "r") as f:
    x = [line.strip() for line in f]

def func(array, radius, max):
    new_array = [['O' for _ in range(len(array[0]))] for _ in range(len(array))]
    accumulator = 0
    for row in range(len(x)):
        for column in range(len(x[0])):
            occurences = 0
            for r_row in range(row-radius, row+radius+1):
                if occurences > max or r_row < 0 or r_row >= len(x):
                    continue
                for r_col in range(column-radius, column+radius+1):
                    if occurences > max or (r_col < 0 or r_col >= len(x[0])) or (r_row == row and r_col == column):
                        continue
                    if array[r_row][r_col] == '@':
                        occurences += 1

            if occurences < max and array[row][column] == '@':
                new_array[row][column] = '.'
                accumulator += 1
            else:
                new_array[row][column] = array[row][column]
            
    new_array = [''.join(l) for l in new_array]

    return accumulator, new_array         

print(func(x, 1, 4)[0])

sum = 0
acc = -1
while acc != 0:
    acc, x = func(x, 1, 4)
    sum += acc

print(sum)