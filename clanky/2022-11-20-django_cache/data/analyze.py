#!/usr/bin/python3
# -*- coding: utf-8 -*-
import argparse
import csv
import json
import random
from pathlib import Path
from collections import defaultdict
import sys

import matplotlib.pyplot as plt
import matplotlib.ticker as mticker
import numpy as np


TESTS = (
	('1_thread_default.tsv', {'group_name': "1 vlákno", 'type_name': "štandardná cache", 'group': '1', 'type': 'default'}),
	('1_thread_new.tsv', {'group_name': "1 vlákno", 'type_name': "upravená cache", 'group': '1', 'type': 'new'}),
	('5_threads_default.tsv', {'group_name': "5 vlákien", 'type_name': "štandardná cache", 'group': '5', 'type': 'default'}),
	('5_threads_new.tsv', {'group_name': "5 vlákien", 'type_name': "upravená cache", 'group': '5', 'type': 'new'}),
)


def load_tests(cur_dir):
	tests = []
	for filename, definition in TESTS:
		with (cur_dir / filename).open('r') as fp:
			reader = csv.reader(fp, delimiter='\t')
			next(reader)
			times = list((int(t[2]), int(t[4])) for t in reader)
			random.shuffle(times)
			times = sorted(times, key=lambda v: v[0])
			times = np.array([v[1] for v in times])
		test_data = definition.copy()
		test_data['data'] = times
		tests.append(test_data)
	return tests


def generate_plots(out_dir, tests):
	fig = plt.figure()
	ax = fig.add_subplot()

	max_time = 0
	count_data = 0
	statistics = []
	for i, data in enumerate(tests):
		if data['type'] == 'default':
			ax.plot(range(len(data['data'])), data['data'], label=data['group_name'], color=f'C{i}')
			max_time = max(max_time, max(data['data']))
			count_data = len(data['data'])

	ax.yaxis.set_major_formatter(mticker.FormatStrFormatter('%d ms'))
	ax.legend()
	ax.set_xlim([0, count_data])
	ax.set_ylim([0, max_time])
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.set_xticks([])
	ax.grid(linestyle='dotted', color='lightgray')
	fig.tight_layout()

	fig.savefig(out_dir / f'time_default.png')
	fig.savefig(out_dir / f'time_default.svg')

	fig = plt.figure(figsize=(2, 5))
	ax = fig.add_subplot()

	statistics = []
	for i, data in enumerate(tests):
		if data['type'] == 'default':
			stat = {
				'mean': np.mean(data['data']),
				'low_high': np.percentile(data['data'], [5, 95]),
				'color': i,
				'data': data,
			}
			statistics.append(stat)
			sys.stdout.write(data['group_name'] + f": {stat['mean']:.0f} ms, low: {stat['low_high'][0]:.0f} ms, high: {stat['low_high'][1]:.0f} ms\n")

	for i, stat in enumerate(statistics):
		ax.bar([i], stat['mean'], width=0.7, label=stat['data']['group_name'], color=f'C{stat["color"]}')
		er = stat['low_high']
		ax.errorbar([i], stat['mean'], yerr=[stat['mean'] - [er[0]], [er[1] - stat['mean']]], color=f'red', capsize=4)
	ax.legend()
	ax.yaxis.set_major_formatter(mticker.FormatStrFormatter('%d ms'))
	ax.set_xticks([])
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)

	fig.tight_layout()

	fig.savefig(out_dir / f'stats_default.png')
	fig.savefig(out_dir / f'stats_default.svg')

	fig = plt.figure()
	ax = fig.add_subplot()

	max_time = 0
	count_data = 0
	statistics = []
	i = 0
	for data in tests:
		if data['type'] == 'new':
			ax.plot(range(len(data['data'])), data['data'], label=data['group_name'], color=f'C{i}')
			max_time = max(max_time, max(data['data']))
			count_data = len(data['data'])
			i += 1

	ax.yaxis.set_major_formatter(mticker.FormatStrFormatter('%d ms'))
	ax.legend()
	ax.set_xlim([0, count_data])
	ax.set_ylim([0, 1000])
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.set_xticks([])
	ax.grid(linestyle='dotted', color='lightgray')
	fig.tight_layout()

	fig.savefig(out_dir / f'time_new.png')
	fig.savefig(out_dir / f'time_new.svg')


	fig = plt.figure(figsize=(4, 5))
	ax = fig.add_subplot()

	statistics = []
	for i, data in enumerate(tests):
		stat = {
			'mean': np.mean(data['data']),
			'low_high': np.percentile(data['data'], [5, 95]),
			'color': i,
			'data': data,
		}
		statistics.append(stat)
		if data['type'] == 'new':
			sys.stdout.write(data['group_name'] + f": {stat['mean']:.0f} ms, low: {stat['low_high'][0]:.0f} ms, high: {stat['low_high'][1]:.0f} ms\n")

	ax.bar(
		[0, 1],
		[statistics[0]['mean'], statistics[2]['mean']],
		width=0.3,
		label=tests[0]['type_name'],
		color=f'C0'
	)
	ax.bar(
		[0.3, 1.3],
		[statistics[1]['mean'], statistics[3]['mean']],
		width=0.3,
		label=tests[1]['type_name'],
		color=f'C1'
	)

	ax.legend()
	ax.grid(linestyle='dotted', color='lightgray')
	ax.set_axisbelow(True)
	ax.yaxis.set_major_formatter(mticker.FormatStrFormatter('%d ms'))
	ax.set_xticks([0.15, 1.15])
	ax.set_xticklabels([tests[0]['group_name'], tests[2]['group_name']])
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)

	fig.tight_layout()

	fig.savefig(out_dir / f'stats_comparison.png')
	fig.savefig(out_dir / f'stats_comparison.svg')


def main():
	cur_dir = Path(__file__).parent
	tests = load_tests(cur_dir)
	generate_plots(cur_dir, tests)


if __name__ == "__main__":
	main()
