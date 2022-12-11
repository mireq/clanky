# -*- coding: utf-8 -*-
from scipy import signal
from scipy.io import wavfile
import matplotlib.pyplot as plt
import numpy as np
import sys

def spectrogram(samples, sample_rate, stride_ms = 10.0,
						  window_ms = 20.0, max_freq = None, eps = 1e-14):

	stride_size = int(0.001 * sample_rate * stride_ms)
	window_size = int(0.001 * sample_rate * window_ms)

	# Extract strided windows
	truncate_size = (len(samples) - window_size) % stride_size
	samples = samples[:len(samples) - truncate_size]
	nshape = (window_size, (len(samples) - window_size) // stride_size + 1)
	nstrides = (samples.strides[0], samples.strides[0] * stride_size)
	windows = np.lib.stride_tricks.as_strided(samples,
										  shape = nshape, strides = nstrides)

	assert np.all(windows[:, 1] == samples[stride_size:(stride_size + window_size)])

	# Window weighting, squared Fast Fourier Transform (fft), scaling
	weighting = np.hanning(window_size)[:, None]

	fft = np.fft.rfft(windows * weighting, axis=0)
	fft = np.absolute(fft)
	fft = fft**2

	scale = np.sum(weighting**2) * sample_rate
	fft[1:-1, :] *= (2.0 / scale)
	fft[(0, -1), :] /= scale

	# Prepare fft frequency list
	freqs = float(sample_rate) / window_size * np.arange(fft.shape[0])

	# Compute spectrogram feature
	ind = np.where(freqs <= max_freq)[0][-1] + 1
	specgram = np.log(fft[:ind, :] + eps)
	return specgram


def main():
	filename = sys.argv[1]
	samplerate, sound = wavfile.read(filename)
	sound = sound[:,0] + sound[:,1]
	sound = sound[2200000:2500000]
	#data = spectrogram(sound, samplerate, max_freq=8192)
	#print(data.shape)

	#plt.imshow(data)
	#plt.show()

	length = sound.shape[0] / samplerate
	f, time, Zxx = signal.stft(sound, samplerate, window='blackmanharris', nperseg=512 * 16, noverlap=512 * 15)
	Zxx = Zxx[0:1024,:]
	f = f[0:1024]
	print(Zxx.shape)
	Zxx = 20.*np.log10(np.abs(Zxx))
	plt.pcolormesh(time, f, np.abs(Zxx), vmin=0, vmax=80, cmap='inferno', shading='nearest')
	plt.colorbar()
	plt.ylim(100, 10240)
	plt.yscale('log')
	plt.title('STFT Magnitude')
	plt.ylabel('Frequency [Hz]')
	plt.xlabel('Time [sec]')
	plt.show()




if __name__ == "__main__":
	main()
