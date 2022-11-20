#!/usr/bin/python3
# -*- coding: utf-8 -*-
import argparse
import json
import subprocess
import sys
import time
from collections import namedtuple
from pathlib import Path


STRENGTH = list(range(2, 0, -1))
TEST_TIME = 15
TEMPERATURE_FILE = '/sys/class/thermal/thermal_zone1/temp'
SYSTEM_WLAN_NAME = 'wlan0'
TIMEOUT = 30


class SignalLost(RuntimeError):
	pass


def human_speed(speed, decimal_places=2):
	for unit in ['bits', 'Kbits', 'Mbits', 'Gbits', 'Tbits', 'Pbits']:
		if speed < 1024.0 or unit == 'Pbits':
			break
		speed /= 1024.0
	return f"{speed:.{decimal_places}f} {unit}"


Stats = namedtuple('Stats', ['link', 'level', 'temp', 'tx_retries'])


# modprobe -r iwlmvm
# modprobe -r iwlwifi
# modprobe iwlmvm power_scheme=1
# modprobe iwlwifi swcrypto=1 power_save=0 bt_coex_active=0
# iw wlan0 set power_save off
# cpupower frequency-set --governor performance

def set_strength(strength, args):
	ret = subprocess.run(['ssh', 'root@' + args.router_ip, 'iwconfig', args.wlan_device, 'txpower', str(strength)], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
	if ret.returncode != 0:
		raise SignalLost()
	time.sleep(5)


def read_stats(proc_wifi_fp, temp_fp):
	proc_wifi_fp.seek(0)
	temp_fp.seek(0)
	try:
		signal_line = proc_wifi_fp.readlines()[2].split()
		link = float(signal_line[2])
		level = float(signal_line[3])
		temp = float(temp_fp.read()) / 1000.0
	except IndexError:
		link = 0.0
		level = 0.0
		temp = 0.0
	retries = 0
	station_dump = [line.strip() for line in subprocess.check_output(['iw', 'dev', 'wlan0', 'station', 'dump']).decode('utf-8').splitlines()]
	station_dump = [line for line in station_dump if line.startswith('tx retries:')]
	if station_dump:
		retries = int(station_dump[0][len('tx retries:'):])
	return Stats(link, level, temp, retries)


def perform_test(directory, test_type, args):
	sum_type = 'sum_sent'
	extra_args = []
	if test_type == 'download':
		extra_args = ['-R']
		sum_type = 'sum_received'
	tx_retries = 0
	extra_statistics = []
	with subprocess.Popen(['iperf3', '-c', args.router_ip, '-p', str(args.port), '-Z'] + extra_args + ['-t', str(TEST_TIME), '-i', '0.5', '--connect-timeout', '1000', '-P', '4', '-J'], stdout=subprocess.PIPE) as proc, open('/proc/net/wireless', 'r') as proc_wifi_fp, open(TEMPERATURE_FILE, 'r') as temp_fp:
		old_stats = read_stats(proc_wifi_fp, temp_fp)
		start_time = time.time()
		while proc.poll() is None:
			stats = read_stats(proc_wifi_fp, temp_fp)
			retries = stats.tx_retries - old_stats.tx_retries
			tx_retries += retries
			old_stats = stats
			time_from_start = time.time() - start_time
			extra_statistics.append({
				'time': time_from_start,
				'link': stats.link,
				'level': stats.level,
				'retries': retries,
				'temp': stats.temp,
			})
			if time_from_start > TIMEOUT:
				proc.kill()
				raise RuntimeError("Iperf timeout")
			time.sleep(0.05)
		if proc.returncode != 0:
			raise SignalLost()
		statistics = json.loads(proc.stdout.read())
	directory.mkdir(parents=True, exist_ok=True)
	with (directory / f'iperf_{test_type}.json').open('w') as fp:
		json.dump(statistics, fp, indent='\t')
	with (directory / f'extra_statistics_{test_type}.json').open('w') as fp:
		extra_statistics = {'tx_retries': tx_retries, 'data': extra_statistics}
		json.dump(extra_statistics, fp, indent='\t')
	speed = statistics['end'][sum_type]['bits_per_second']
	sys.stdout.write(f'    {human_speed(speed)}/s ({tx_retries} tx retries)')
	sys.stdout.flush()


def perform_tests(args):
	output_dir = Path(args.output_directory)
	output_dir.mkdir(parents=True, exist_ok=True)
	output_dir = output_dir / args.wlan_device
	output_dir.mkdir(parents=True, exist_ok=True)

	sys.stdout.write(f"Writing test to directory: {str(output_dir.absolute())}\n")
	sys.stdout.write(f"Router: {args.router_ip}\n")
	sys.stdout.write(f"Wlan device: {args.wlan_device}\n")
	sys.stdout.write(f"Port: {args.port}\n\n")

	for strength in STRENGTH:
		strength = str(strength)
		directory = output_dir / strength
		sys.stdout.write(f"{strength} dBm")
		sys.stdout.flush()
		try:
			while True:
				try:
					set_strength(strength, args)
					perform_test(directory, 'download', args)
					perform_test(directory, 'upload', args)
				#except SignalLost:
				#	raise
				except Exception as e:
					sys.stderr.write(str(e) + "\n")
					continue
				break
		except SignalLost:
			sys.stdout.write(" signal lost\nEnd of test\n")
			break
		sys.stdout.write("\n")


def main():
	parser = argparse.ArgumentParser(prog="Network performance tester")
	parser.add_argument('output_directory', help="Output directory")
	parser.add_argument('router_ip', help="Router IP address")
	parser.add_argument('wlan_device', help="Wlan device on router like wl0")
	parser.add_argument('--port', type=int, default=5201)
	args = parser.parse_args()
	perform_tests(args)


if __name__ == "__main__":
	main()



#import os
#import subprocess
#import sys
#import time
#
#
#def perform_test2(extra_args, name):
#	directory = sys.argv[1]
#	server = sys.argv[2]
#	port = sys.argv[3]
#	with subprocess.Popen(['iperf3', '-c', server, '-p', port, '-Z'] + extra_args + ['-t', '60', '-i', '0.5', '-J', '--logfile', os.path.join(directory, f'{name}.json')], stdout=subprocess.PIPE, stderr=subprocess.PIPE) as proc:
#		with open(os.path.join(directory, f'{name}_stats.csv'), 'w') as stats_fp:
#			with open('/proc/net/wireless', 'r') as proc_wifi_fp:
#				with open('/sys/class/thermal/thermal_zone2/temp', 'r') as temp_fp:
#					start_time = time.time()
#					stats_fp.write('time,link,level,temp\n')
#					while proc.poll() is None:
#						time.sleep(0.002)
#						proc_wifi_fp.seek(0)
#						temp_fp.seek(0)
#						try:
#							signal_line = proc_wifi_fp.readlines()[2].split()
#							link = float(signal_line[2])
#							level = float(signal_line[3])
#							temp = float(temp_fp.read()) / 1000.0
#						except IndexError:
#							link = 0.0
#							level = 0.0
#							temp = 0.0
#						time_from_start = time.time() - start_time
#						stats_fp.write(f'{time_from_start},{link},{level},{temp}\n')
#
#
#def main():
#	if len(sys.argv) != 4:
#		sys.stderr.write(f'Usege {sys.argv[0]} directory server port\n')
#		sys.exit(-1)
#	directory = sys.argv[1]
#	os.makedirs(directory, exist_ok=True)
#	for performance in range(30, 10, -1):
#		outdir = os.path.join(directory, str(performance))
#		os.makedirs(outdir, exist_ok=True)
#		print(performance)
#
#	#perform_test(['-R'], 'download')
#	#perform_test([], 'upload')
#
#
# port 5201
