# -*- coding: utf-8 -*-
import os
import subprocess
import sys
import time


def perform_test(extra_args, name):
	directory = sys.argv[1]
	server = sys.argv[2]
	port = sys.argv[3]
	with subprocess.Popen(['iperf3', '-c', server, '-p', port, '-Z'] + extra_args + ['-t', '60', '-i', '0.5', '-J', '--logfile', os.path.join(directory, f'{name}.json')], stdout=subprocess.PIPE, stderr=subprocess.PIPE) as proc:
		with open(os.path.join(directory, f'{name}_signal.csv'), 'w') as signal_fp:
			with open('/proc/net/wireless', 'r') as proc_wifi_fp:
				start_time = time.time()
				signal_fp.write('time,link,level\n')
				while proc.poll() is None:
					time.sleep(0.002)
					proc_wifi_fp.seek(0)
					try:
						signal_line = proc_wifi_fp.readlines()[2].split()
						link = float(signal_line[2])
						level = float(signal_line[3])
					except IndexError:
						link = 0.0
						level = 0.0
					time_from_start = time.time() - start_time
					signal_fp.write(f'{time_from_start},{link},{level}\n')


def main():
	if len(sys.argv) != 4:
		sys.stderr.write(f'Usege {sys.argv[0]} directory server port\n')
		sys.exit(-1)
	directory = sys.argv[1]
	os.makedirs(directory)
	perform_test(['-R'], 'download')
	perform_test([], 'upload')


if __name__ == "__main__":
	main()
