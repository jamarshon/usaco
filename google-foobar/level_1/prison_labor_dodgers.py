def answer(x, y):
    if len(x) > len(y): 
        x,y = y,x
    freq = {}
    for d in x:
        if d in freq:
            freq[d] += 1
        else:
            freq[d] = 1
    for d in y:
        if d not in freq or freq[d] is 0:
            return d
        else:
            freq[d] -= 1
    return -1

x = [13, 5, 6, 2, 5]
y = [5, 2, 5, 13]
print answer(x,y), 6


x = [14, 27, 1, 4, 2, 50, 3, 1]
y = [2, 4, -4, 3, 1, 1, 14, 27, 50]
print answer(x,y), -4