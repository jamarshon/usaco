import math
def recurse(N, target, interval):
    left_child = N - int(interval/2) - 1
    right_child = N - 1
    interval = interval/2
    # print left_child, right_child
    if left_child == target or right_child == target:
        return N
    elif left_child < target <= right_child:
        return recurse(right_child, target, interval)
    else:
        return recurse(left_child, target, interval)
        

def answer(h, q):
    result = []
    N = math.pow(2, h) - 1
    for e in q:
        if e == N:
            result.append(-1)
        else:
            result.append(recurse(N, e, N))
    return result

print answer(3, [7, 3, 5, 1])
print answer(5, [19, 14, 28])
