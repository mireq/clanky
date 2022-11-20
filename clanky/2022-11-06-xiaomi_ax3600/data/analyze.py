#!/usr/bin/python3
# -*- coding: utf-8 -*-
import argparse
import json
from pathlib import Path
from collections import defaultdict

import matplotlib.pyplot as plt
import matplotlib.ticker as mticker
import numpy as np


DEVICE_NAME_MAP = {
	'wl0': "5 GHz",
	'wl1': "2.4 GHz",
}


def human_speed(speed, decimal_places=2):
	speed = speed / (1024*1024)
	return f"{speed:.0f} Mbps"


def get_txpower_list(src_dir):
	power_list = []
	for subdir in src_dir.iterdir():
		if not subdir.is_dir():
			continue
		try:
			power_list.append(int(subdir.name))
		except ValueError:
			pass
	power_list.sort()
	return power_list


def load_data(src_dir, metric_type):
	with (src_dir / f'iperf_{metric_type}.json').open('r') as iperf_fp, (src_dir / f'extra_statistics_{metric_type}.json').open('r') as extra_stats_fp:
		iperf = json.load(iperf_fp)
		extra_stats = json.load(extra_stats_fp)
	iperf['extra_stats'] = extra_stats
	return iperf


def get_duration(data):
	return data['start']['test_start']['duration']


def fix_extra_stats_timestamps(data, test_duration):
	last_time = data['extra_stats']['data'][-1]['time']
	time_diff = test_duration - last_time
	return [{
		'time': item['time'] + time_diff,
		'link': item['link'] * 10 / 7,
		'level': item['level'],
		'retries': item['retries'],
		'temp': item['temp'],
	} for item in data['extra_stats']['data'] if item['time'] + time_diff >= 0]


def get_stats_from_list(values):
	if not values:
		return {
			'mean': None,
			'stdev': 0,
			'percentiles': [0] * 7,
		}
	array = np.asarray(values)
	mean = array.mean()
	stdev = array.std()
	percentiles = [5, 10, 20, 50, 80, 90, 95]
	percentiles = {percentile: val for percentile, val in zip(percentiles, np.percentile(array, [val / 100.0 for val in percentiles]))}
	return {
		'mean': mean,
		'stdev': stdev,
		'percentiles': percentiles,
	}


def write_analysis(out_dir, data):
	out_dir.mkdir(parents=True, exist_ok=True)

	performance = set()
	for device_data in data.values():
		performance = performance.union(device_data['download'].keys())
		performance = performance.union(device_data['upload'].keys())

	performance = list(sorted(list(performance)))
	performance_index = {val: i for i, val in enumerate(performance)}

	link_values_list = {dev: {perf: [] for perf in performance} for dev in data.keys()}
	level_values_list = {dev: {perf: [] for perf in performance} for dev in data.keys()}
	speed = {metric_type: {dev: np.zeros(len(performance)) for dev in data.keys()} for metric_type in ['download', 'upload']}
	speeds = {metric_type: {dev: [[]] * len(performance) for dev in data.keys()} for metric_type in ['download', 'upload']}
	speed_stdev = {metric_type: {dev: np.zeros(len(performance)) for dev in data.keys()} for metric_type in ['download', 'upload']}

	for device, device_data in data.items():
		for metric_type, metric_data in device_data.items():
			for perf, test_data in metric_data.items():
				test_duration = get_duration(test_data)
				test_data['extra_stats']['data'] = fix_extra_stats_timestamps(test_data, test_duration)
				link_values_list[device][perf].extend([item['link'] for item in test_data['extra_stats']['data']])
				level_values_list[device][perf].extend([item['level'] for item in test_data['extra_stats']['data']])
				cumulative_time = 0
				cumulative_bytes = 0
				intervals = test_data['intervals']
				intervals = sorted(intervals, key=lambda v: v['sum']['bits_per_second'], reverse=True)
				for interval in intervals:
					speeds[metric_type][device][performance_index[perf]].append(interval['sum']['bits_per_second'])
					cumulative_time += interval['sum']['seconds']
					cumulative_bytes += interval['sum']['bytes']
					if cumulative_time > test_duration / 4:
						break
				speed[metric_type][device][performance_index[perf]] = cumulative_bytes * 8 / cumulative_time
				speed_stats = get_stats_from_list(speeds[metric_type][device][performance_index[perf]])
				speed_stdev[metric_type][device][performance_index[perf]] = speed_stats['stdev']

	link_value = {dev: np.zeros(len(performance)) for dev in data.keys()}
	link_stdev = {dev: np.zeros(len(performance)) for dev in data.keys()}
	level_value = {dev: np.zeros(len(performance)) for dev in data.keys()}
	level_stdev = {dev: np.zeros(len(performance)) for dev in data.keys()}

	for dev in data.keys():
		for perf, values in link_values_list[dev].items():
			stats = get_stats_from_list(values)
			idx = performance_index[perf]
			link_value[dev][idx] = stats['mean']
			link_stdev[dev][idx] = stats['stdev']
		for perf, values in level_values_list[dev].items():
			stats = get_stats_from_list(values)
			idx = performance_index[perf]
			level_value[dev][idx] = stats['mean']
			level_stdev[dev][idx] = stats['stdev']

	fig = plt.figure()
	ax = fig.add_subplot()
	color_num = 0
	for dev, values in link_value.items():
		ax.plot(performance, values, label=DEVICE_NAME_MAP.get(dev, dev), color=f'C{color_num}')
		ax.fill_between(performance, values - link_stdev[dev], values + link_stdev[dev], alpha=0.1, facecolor=f'C{color_num}')
		color_num += 1
	ax.xaxis.set_major_formatter(mticker.FormatStrFormatter('%d dBm'))
	ax.yaxis.set_major_formatter(mticker.FormatStrFormatter('%d %%'))
	ax.legend()
	ax.set_title("Kvalita signálu")
	ax.set_xlim([1, max(performance)])
	ax.set_ylim([0, 100])
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.grid(linestyle='dotted', color='lightgray')
	ax.invert_xaxis()
	fig.tight_layout()

	fig.savefig(out_dir / f'link_quality.png')
	fig.savefig(out_dir / f'link_quality.svg')

	fig = plt.figure()
	ax = fig.add_subplot()
	color_num = 0
	for dev, values in level_value.items():
		ax.plot(performance, values, label=DEVICE_NAME_MAP.get(dev, dev), color=f'C{color_num}')
		ax.fill_between(performance, values - level_stdev[dev], values + level_stdev[dev], alpha=0.1, facecolor=f'C{color_num}')
		color_num += 1
	ax.xaxis.set_major_formatter(mticker.FormatStrFormatter('%d dBm'))
	ax.yaxis.set_major_formatter(mticker.FormatStrFormatter('%d dBm'))
	ax.legend()
	ax.set_title("Sila signálu")
	ax.set_xlim([1, max(performance)])
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.grid(linestyle='dotted', color='lightgray')
	ax.invert_xaxis()
	fig.tight_layout()

	fig.savefig(out_dir / f'level.png')
	fig.savefig(out_dir / f'level.svg')

	fig = plt.figure()
	ax = fig.add_subplot()
	color_num = 0
	max_speed = 0
	for dev, values in speed['download'].items():
		ax.plot(performance, values, label=DEVICE_NAME_MAP.get(dev, dev), color=f'C{color_num}')
		ax.fill_between(performance, values - speed_stdev['download'][dev], values + speed_stdev['download'][dev], alpha=0.1, facecolor=f'C{color_num}')
		max_speed = max(max_speed, max(speed['download'][dev] + speed_stdev['download'][dev]))
		color_num += 1
	ax.xaxis.set_major_formatter(mticker.FormatStrFormatter('%d dBm'))
	ax.yaxis.set_major_formatter(mticker.FuncFormatter(lambda x, pos: human_speed(x)))
	ax.legend()
	ax.set_title("Sťahovanie")
	ax.set_xlim([1, max(performance)])
	ax.set_ylim([0, max_speed])
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.grid(linestyle='dotted', color='lightgray')
	ax.invert_xaxis()
	ax.set_yticks(np.arange(0, max_speed, 104857600))
	fig.tight_layout()

	fig.savefig(out_dir / f'download.png')
	fig.savefig(out_dir / f'download.svg')

	fig = plt.figure()
	ax = fig.add_subplot()
	color_num = 0
	max_speed = 0
	for dev, values in speed['upload'].items():
		ax.plot(performance, values, label=DEVICE_NAME_MAP.get(dev, dev), color=f'C{color_num}')
		ax.fill_between(performance, values - speed_stdev['upload'][dev], values + speed_stdev['upload'][dev], alpha=0.1, facecolor=f'C{color_num}')
		max_speed = max(max_speed, max(speed['upload'][dev] + speed_stdev['upload'][dev]))
		color_num += 1
	ax.xaxis.set_major_formatter(mticker.FormatStrFormatter('%d dBm'))
	ax.yaxis.set_major_formatter(mticker.FuncFormatter(lambda x, pos: human_speed(x)))
	ax.legend()
	ax.set_title("Odosielanie")
	ax.set_xlim([1, max(performance)])
	ax.set_ylim([0, max_speed])
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.grid(linestyle='dotted', color='lightgray')
	ax.invert_xaxis()
	ax.set_yticks(np.arange(0, max_speed, 104857600))
	fig.tight_layout()

	fig.savefig(out_dir / f'upload.png')
	fig.savefig(out_dir / f'upload.svg')


def get_device_data(src_dir):
	power_list = get_txpower_list(src_dir)
	download_data = {}
	upload_data = {}
	for power in power_list:
		data = load_data(src_dir / str(power), 'download')
		download_data[power] = data
		data = load_data(src_dir / str(power), 'upload')
		upload_data[power] = data
	return {'download': download_data, 'upload': upload_data}
	#write_analysis(out_dir / src_dir.name, 'download', download_data)
	#write_analysis(out_dir / src_dir.name, 'upload', upload_data)


def perform_analysis(args):
	src_dir = Path(args.source_directory)
	out_dir = Path(args.output_directory)
	out_dir.mkdir(parents=True, exist_ok=True)
	data = {}
	for subdir in src_dir.iterdir():
		if not subdir.is_dir():
			continue
		data[subdir.name] = get_device_data(subdir)
	write_analysis(out_dir, data)


def main():
	parser = argparse.ArgumentParser(prog="Network performance tester")
	parser.add_argument('source_directory', help="Source directory")
	parser.add_argument('output_directory', help="Output directory")
	args = parser.parse_args()
	perform_analysis(args)


if __name__ == "__main__":
	main()
