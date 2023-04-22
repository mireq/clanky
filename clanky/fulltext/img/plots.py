# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path


out_dir = Path(__file__).parent


def plot(output, server, test_name, data, ylim=None):
	fig = plt.figure(figsize=[4, 5])
	ax = fig.add_subplot()

	x_axis = np.arange(len(server))

	width = 0.25
	for i, test_data in enumerate(zip(test_name, data)):
		test_name, test_data = test_data
		bars = plt.bar(x_axis+width * i, test_data, width=width, label=test_name)
		ax.bar_label(bars, rotation=90)

	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)

	ax.set_xticks(np.arange(len(server)), server, rotation=45)
	if ylim is not None:
		ax.set_ylim(ylim)
	ax.set_ylabel('ms')
	ax.legend()


	fig.tight_layout()
	fig.savefig(out_dir / output)


def main():
	server = ['MySQL', 'PG GIN', 'PG RUM']
	test_name = ['bežné', 'zriedkavé', 'kombinácia']
	data = [
		[383, 2.662, 5.087],
		[1, 0.444, 0.595],
		[7, 0.711, 0.748],
	]

	plot('search_speed.svg', server, test_name, data)
	plot('search_speed_crop.svg', server, test_name, data, ylim=[0, 10])

	server = ['MySQL', 'PG GIN']
	data = [
		[372, 66.747],
		[2, 1.362],
		[10, 1.207],
	]
	plot('sort.svg', server, test_name, data)

	server = ['MySQL', 'PG GIN', 'PG RUM']
	data = [
		[372, 66.747, 5.757],
		[2, 1.362, 0.901],
		[10, 1.207, 0.974],
	]
	plot('sort_rum.svg', server, test_name, data, ylim=[0, 70])


if __name__ == "__main__":
	main()
