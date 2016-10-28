import os
import sys
import numpy as np
import math
from scipy.signal import get_window
from scipy.stats import signaltonoise
import matplotlib.pyplot as plt

sys.path.append(os.path.join(os.path.dirname(os.path.realpath(__file__)), '../../software/models/'))
import stft
import utilFunctions as UF
eps = np.finfo(float).eps


"""
A4-Part-2: Measuring noise in the reconstructed signal using the STFT model 

Write a function that measures the amount of noise introduced during the analysis and synthesis of a 
signal using the STFT model. Use SNR (signal to noise ratio) in dB to quantify the amount of noise. 
Use the stft() function in stft.py to do an analysis followed by a synthesis of the input signal.

A brief description of the SNR computation can be found in the pdf document (A4-STFT.pdf, in Relevant 
Concepts section) in the assignment directory (A4). Use the time domain energy definition to compute
the SNR.

With the input signal and the obtained output, compute two different SNR values for the following cases:

1) SNR1: Over the entire length of the input and the output signals.
2) SNR2: For the segment of the signals left after discarding M samples from both the start and the 
end, where M is the analysis window length. Note that this computation is done after STFT analysis 
and synthesis.

The input arguments to the function are the wav file name including the path (inputFile), window 
type (window), window length (M), FFT size (N), and hop size (H). The function should return a python 
tuple of both the SNR values in decibels: (SNR1, SNR2). Both SNR1 and SNR2 are float values. 

Test case 1: If you run your code using piano.wav file with 'blackman' window, M = 513, N = 2048 and 
H = 128, the output SNR values should be around: (67.57748352378475, 304.68394693221649).

Test case 2: If you run your code using sax-phrase-short.wav file with 'hamming' window, M = 512, 
N = 1024 and H = 64, the output SNR values should be around: (89.510506656299285, 306.18696700251388).

Test case 3: If you run your code using rain.wav file with 'hann' window, M = 1024, N = 2048 and 
H = 128, the output SNR values should be around: (74.631476225366825, 304.26918192997738).

Due to precision differences on different machines/hardware, compared to the expected SNR values, your 
output values can differ by +/-10dB for SNR1 and +/-100dB for SNR2.
"""

def computeSNR(inputFile, window, M, N, H):
    """
    Input:
            inputFile (string): wav file name including the path 
            window (string): analysis window type (choice of rectangular, triangular, hanning, hamming, 
                    blackman, blackmanharris)
            M (integer): analysis window length (odd positive integer)
            N (integer): fft size (power of two, > M)
            H (integer): hop size for the stft computation
    Output:
            The function should return a python tuple of both the SNR values (SNR1, SNR2)
            SNR1 and SNR2 are floats.
    """
    sr, x = UF.wavread(inputFile)
    w = get_window(window, M)
    # mY, pY = stft.stftAnal(x, w, N, H)
    # x2 = stft.stftSynth(mY, pY, M, H)
    x2 = stft.stft(x, w, N, H)

    noise = np.abs(x2 - x)

    e = sum([abs(s**2) for s in x])
    e2 = sum([abs(s**2) for s in x2])
    en = sum([abs(s**2) for s in noise])

    snr1 = 10. * np.log10(e/en)

    noise = np.abs(x2[M:-M] - x[M:-M])

    e = sum([abs(s**2) for s in x[M:-M]])
    e2 = sum([abs(s**2) for s in x2[M:-M]])
    en = sum([abs(s**2) for s in noise[M:-M]])

    snr2 = 10. * np.log10(e/en)

    return snr1, snr2

if __name__ == "__main__":
    snr1, snr2 = computeSNR("../../../sounds/piano.wav", "blackman", 513, 2048, 128)
    print(snr1, snr2)
    snr1, snr2 = computeSNR("../../../sounds/sax-phrase-short.wav", "hamming", 512, 1024, 64)
    print(snr1, snr2)
    snr1, snr2 = computeSNR("../../../sounds/rain.wav", "hann", 1024, 2048, 128)
    print(snr1, snr2)
