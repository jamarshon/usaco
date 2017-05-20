def answer(data, n):
    freq = {}
    for d in data:
        if d in freq:
            freq[d] += 1
        else:
            freq[d] = 1

    res = []
    for d in data:
        if freq[d] <= n:
            res.append(d)
    return res

data = [1, 2, 3]
n = 0
print answer(data, n), []


data = [1, 2, 2, 3, 3, 3, 4, 5, 5]
n = 1
print answer(data, n), [1, 4]


data = [1, 2, 3]
n = 6
print answer(data, n), [1, 2, 3]