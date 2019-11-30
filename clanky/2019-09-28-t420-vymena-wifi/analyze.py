# -*- coding: utf-8 -*-
import json
import os
import sys


def analyze(name):
	directory = sys.argv[1]
	with open(os.path.join(directory, f'{name}_signal.csv'), 'r') as signal_fp:
		with open(os.path.join(directory, f'{name}.json'), 'r') as iperf_fp:
			iperf_data = json.load(iperf_fp)
			total_time = iperf_data['end']['sum_sent']['end']
			signal_fp.readline()
			signal_data = [tuple(float(value) for value in line.split(',')) for line in signal_fp.readlines()]
			last_signal_time = signal_data[-1][0]
			time_compensation = total_time - last_signal_time
			signal_data = [(line[0] + time_compensation,) + line[1:] for line in signal_data]
			with open(os.path.join(directory, f'{name}_analyze.csv'), 'w') as analyze_fp:
				analyze_fp.write('time,speed,line,level\n')
				for interval in iperf_data['intervals']:
					interval = interval['sum']
					interval_signal_data = [line for line in signal_data if line[0] >= interval['start'] and line[0] <= interval['end']]
					time = interval['start']
					speed = interval['bits_per_second'] / 1024**2
					line_quality = sum(line[1] for line in interval_signal_data) / len(interval_signal_data)
					link_level = sum(line[2] for line in interval_signal_data) / len(interval_signal_data)
					analyze_fp.write(f'{time},{speed},{line_quality},{link_level}\n')


def main():
	if len(sys.argv) != 2:
		sys.stderr.write(f'Usege {sys.argv[0]} directory\n')
		sys.exit(-1)
	analyze('download')
	analyze('upload')


if __name__ == "__main__":
	main()
