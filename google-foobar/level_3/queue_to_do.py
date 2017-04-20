def answer(start, length):
    retAns = 0;
    for i in range(length):
        begin = start + i*length
        for j in range(begin, begin + length - i):
            retAns ^=j
    return retAns
    
# print answer(0, 3)
# print answer(17, 4)
print answer(0, 3) == 2
print answer(17, 4) == 14