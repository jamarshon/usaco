# compute x - y in base b
def subtract(x, y, b, k):
	result = [0]*k
	for i in range(k - 1, -1, -1):
		if x[i] == -1:
			x[i - 1] = x[i - 1] - 1
			x[i] = b - 1
		if x[i] >= y[i]:
			result[i] = x[i] - y[i]
		else:
			x[i - 1] = x[i - 1] - 1
			x[i] = x[i] + b
			result[i] = x[i] - y[i]
	return result

def get_new_n(n, b, k):
	n_list = sorted(n)
	return subtract(n_list[::-1], n_list , b, k)

def answer(n, b):
	seen_n = {}
	n_list = map(lambda c: int(c), n)
	k = len(n)
	result = -1
	i = 0
	while True:
		seen_n[str(n_list)] = i
		new_n = get_new_n(n_list, b, k)
		i = i + 1

		if str(new_n) in seen_n:
			result = i - seen_n[str(new_n)]
			break

		n_list = new_n

	return result

print answer('1211', 10)
print answer('210022', 3)