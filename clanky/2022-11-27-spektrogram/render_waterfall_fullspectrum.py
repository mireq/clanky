# -*- coding: utf-8 -*-
import argparse
import shlex
import subprocess
import json
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.transforms import Bbox
from matplotlib.ticker import FormatStrFormatter
from scipy import signal


FFPROBE_BINARY = 'ffprobe'
FFMPEG_BINARY = 'ffmpeg'


FFPROBE_CMDLINE = '{ffprobe} {file} -print_format json -show_format -show_streams -loglevel error'
FFMPEG_AUDIO_INPUT = '{ffmpeg} -i {file} -ac 1 -f s16le -vn -loglevel error -'


def build_shell_command(cmd, replacements):
	"""
	Replace {variable} with dictionary of replacements
	"""

	# Split to tokens
	params = shlex.split(cmd)

	# Build lookup table for replacements
	replacements = {'{'+key+'}': val for key, val in replacements.items()}

	new_params = []
	for param in params:
		# Find replacement
		replacement = replacements.get(param, param)
		# None value removes replacement
		if replacement is None:
			continue
		elif isinstance(replacement, list):
			# List is added to arguments
			new_params += replacement
		else:
			# Single value replaces placeholder
			new_params.append(replacement)
	return new_params


def get_media_info(file):
	"""
	Read media info using ffprobe utility
	"""
	cmd = build_shell_command(FFPROBE_CMDLINE, {'ffprobe': FFPROBE_BINARY, 'file': file})
	return json.loads(subprocess.check_output(cmd))


def get_audio_info(media_info):
	"""
	Finds first audio stream
	"""
	for stream in media_info['streams']:
		if stream['codec_type'] == 'audio':
			return stream


def read_audio(args, audio_info):
	"""
	Returns audio sample rate and samples
	"""
	cmd = build_shell_command(FFMPEG_AUDIO_INPUT, {'ffmpeg': FFMPEG_BINARY, 'file': args.file})
	stream = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
	data = stream.stdout.read()
	data = np.frombuffer(data, dtype=np.int16).astype(float)
	sample_rate = int(audio_info['sample_rate'])
	if args.start is not None or args.length is not None:
		start = int((args.start or 0) * sample_rate)
		end = None
		if args.length != None:
			end = int(args.length * sample_rate + start)
		data = data[start:end]

	data /= (2**15)
	return {
		'sample_rate': sample_rate,
		'samples': data,
	}


def analyze_audio(args, audio_data):
	frequency, time, fft = signal.stft(
		audio_data['samples'],
		audio_data['sample_rate'],
		window=args.window,
		nperseg=8192,
		noverlap=8192-512
	)
	fft = np.abs(fft)
	fft = 20.*np.log10(fft)

	#frequency = frequency[1:1025]
	#fft = fft[1:1025,:]

	return frequency, time, fft



def main():
	parser = argparse.ArgumentParser()
	parser.add_argument('file', help="Multimedia file")
	parser.add_argument('output', help="Output image")
	parser.add_argument('--start', type=float, help="Start second")
	parser.add_argument('--length', type=float, help="Length of audio")
	parser.add_argument('--window', type=str, default='blackmanharris', help="Window function")
	args = parser.parse_args()
	audio_info = get_audio_info(get_media_info(args.file))
	audio_data = read_audio(args, audio_info)
	frequency, time, fft = analyze_audio(args, audio_data)

	px = 1/plt.rcParams['figure.dpi']

	image_size = (fft.shape[1] + 100, 800)

	fig = plt.figure(figsize=(image_size[0]*px, image_size[1]*px))

	ax = fig.add_subplot(position=Bbox([[1, 1], [10, 10]]))
	ax.pcolormesh(time, frequency, fft, vmax=-30, vmin=-100, cmap='inferno', shading='nearest')
	ax.set_ylim(80, 5000)
	ax.yaxis.set_minor_formatter(FormatStrFormatter("%.1f"))
	ax.set_yscale('log')
	ax.set_ylabel('Frequency [Hz]')
	ax.set_xlabel('Time [sec]')
	ax.grid(color='#ffffff', axis='y', which='major', alpha=0.5)
	ax.grid(linestyle='dotted', color='#ffffff', axis='y', which='minor', alpha=0.3)
	fig.subplots_adjust(left=100/image_size[0], right=1, top=1, bottom=60/image_size[1])

	fig.savefig(args.output)


if __name__ == "__main__":
	main()
