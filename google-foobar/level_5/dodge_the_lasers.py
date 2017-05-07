frac_sqrt_2 = 4142135623730950488016887242096980785696718753769480731766797379907324784621070388503875343276415727
precision = len(str(frac_sqrt_2))

def compute_n_prime(n):
    new_n = str(n * frac_sqrt_2)
    # computes floor((sqrt(2) - 1)*n which is equivalent to truncating based on len 
    return 0 if len(new_n) <= precision else int(new_n[:len(new_n) - precision])

# formula based on summation of A001951 A Beatty sequence: a(n) = floor(n*sqrt(2))
# S(a, n) = sum_k=1 to n { floor(a*k)} where a is an irrational positive number
# if a >= 2, let b = a - 1
#   S(a, n) = S(b, n) + sum_k=1 to n { k }
#           = S(b, n) + n(n + 1)/2
# let n_prime = floor((a-1)*n), then
#   S(a, n) =  (n + n_prime)*(n + n_prime + 1)/2 - S(b, n_prime)
# when a = sqrt(2) and b = 2 + sqrt(2) then
#   S(sqrt(2), n) = n*n_prime + n*(n + 1)/2 - n_prime*(n_prime + 1) - S(sqrt(2), n_prime)
def S(n):
    if n == 0: return 0
    new_n = compute_n_prime(n)
    return n*new_n + n*(n + 1)/2 - new_n*(new_n + 1)/2 - S(new_n)

def answer(str_n):
    n = int(str_n)
    return S(n)

print answer(77)
