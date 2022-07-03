# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import numpy as np


with plt.xkcd():
	plt.rcParams.update({'font.size': 24})

	fig = plt.figure(figsize=(12, 3), dpi=96)
	ax = fig.add_axes((0, 0.2, 1, 1))
	ax.spines['top'].set_visible(False)
	ax.spines['left'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.set_xlim([0, 12])
	ax.set_ylim([0, 3])

	plt.xticks([1, 3, 4, 6, 8, 9], ['r-1', 's-1', 'e-1', 'r-2', 's-2', 'e-2'])

	ax.plot([0, 4, 4, 6, 6, 9, 9, 12], [2, 2, 0.1, 0.1, 2, 2, 0.1, 0.1], color='C0')

	plt.show()
