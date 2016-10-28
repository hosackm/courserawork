import numpy as np

"""
A2-Part-3: Implement the discrete Fourier transform (DFT)

Write a function that implements the discrete Fourier transform (DFT). Given a sequence x of length
N, the function should return its DFT, its spectrum of length N with the frequency indexes ranging from 0 
to N-1.

The input argument to the function is a numpy array x and the function should return a numpy array X which 
is of the DFT of x.

EXAMPLE: If you run your function using x = np.array([1, 2, 3, 4]), the function shoulds return the following numpy array:
array([10.0 + 0.0j,  -2. +2.0j,  -2.0 - 9.79717439e-16j, -2.0 - 2.0j])

Note that you might not get an exact 0 in the output because of the small numerical errors due to the
limited precision of the data in your computer. Usually these errors are of the order 1e-15 depending
on your machine.
"""
def DFT(x):
    """
    Input:
        x (numpy array) = input sequence of length N
    Output:
        The function should return a numpy array of length N
        X (numpy array) = The N point DFT of the input sequence x
    """
    return np.array([np.sum(x * np.conjugate(s))
    	             for s in [np.exp(2.0j * np.pi * k / len(x) * np.arange(len(x)))
    	                       for k in xrange(len(x))]])

if __name__ == "__main__":
	import matplotlib.pyplot as plt
	N = 64
	k0 = 7
	x = np.exp(2.0j * np.pi * k0 / N * np.arange(N))

	plt.stem(np.arange(N), abs(DFT(x)))
	plt.axis([0, N-1, 0, N])
	plt.show()
