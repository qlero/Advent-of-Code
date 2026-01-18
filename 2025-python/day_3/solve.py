with open("data.txt", "r") as f:
    x = [line.strip() for line in f]

def func(x, n):
    accumulator = 0
    digit_place = 10**(n-1)
    index       = 0
    print(x)
    for i in range(n)[::-1]:
        print("indeX", index)
        placeholder = x[:len(x)-i]
        max_value   = -1
        for j in range(index,len(x)-i):
            if int(placeholder[j]) > max_value:
                max_value    = int(placeholder[j])
                print(max_value, index, i, digit_place)
                index        = j
                # print(max_value)
            else:
                accumulator += int(max_value * digit_place)
                digit_place /= 10
                index       += 1
                break
                # print(accumulator, digit_place, index)
            
        print(accumulator)
    return accumulator

def func2(x, n):
    # create array of ints
    x = list(map(lambda i: int(i), x))
    # create placeholders
    accumulator = 0
    digit_place = 10**(n-1)
    index       = 0
    for i in range(n)[::-1]:
        placeholder   = x[index:len(x)-i]
        max_value     = max(placeholder)
        index         = index + placeholder.index(max_value)+1
        accumulator  += digit_place * max_value
        digit_place //= 10  
    return accumulator

acc = 0
for val in x:
    acc += func2(val, 12)
print(acc)