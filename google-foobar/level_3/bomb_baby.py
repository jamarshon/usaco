def answer(M, F):
    generations = 0
    temp = 0
    M = int(M)
    F = int(F)
    if M < F:
        temp = F
        F = M
        M = temp
    while True:
        if M <= 0 or F <= 0: return 'impossible'
        if M == 1 or F == 1: return generations + max(M, F) - 1
        # ensure M > F
        generations = generations + int(M/F)
        temp = M % F
        M = F
        F = temp

print answer(2, 1)
print answer(4, 7)
print answer(2, 4)

