import numpy as np



def double_plus_single(x,y):
	print(x,y)
	return 2*x+y

double_plus = np.vectorize(double_plus_single, otypes= [np.float])

ints = np.array([[1,2],[3,4]], dtype = np.int64)

results = double_plus(ints[0],ints[1])

print(results)

