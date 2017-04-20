import math
def answer(n):
    n = int(n)
    dp = {}
    return recurse(n, dp)

def recurse(n, dp):
    if n in dp: return dp[n]
    if n == 1:
        return 0
    smallest_set_bit = n & ~(n - 1)
    if n % 2 == 0:
        ans = recurse(n/smallest_set_bit, dp)
        dp[n/smallest_set_bit] = ans
        return int(math.log(smallest_set_bit, 2)) + ans

    smallest_zero_bit = ~n & (n + 1)
    index_zero_bit = int(math.log(smallest_zero_bit, 2))
    temp = n >> index_zero_bit
    if temp == 0:
        return min(index_zero_bit + 1, (index_zero_bit - 1)*2)

    ans1 = recurse(temp, dp)
    ans2 = recurse(temp + 1, dp)
    dp[temp] = ans1
    dp[temp + 1] = ans2
    return min(2*index_zero_bit + ans1, index_zero_bit + 1 + ans2)