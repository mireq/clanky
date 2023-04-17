# -*- coding: utf-8 -*-
import matplotlib.lines as mlines
import matplotlib.pyplot as plt


with plt.xkcd():
	plt.rcParams.update({'font.size': 16})

	fig = plt.figure(figsize=(3, 5), dpi=96)
	ax = fig.add_axes((0.05, 0.05, 0.9, 0.9))
	ax.spines['top'].set_visible(False)
	ax.spines['left'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.spines['bottom'].set_visible(False)

	next_cell = 0.0333 + 0.3/5
	ax.add_line(mlines.Line2D([0.53, 0.57, 0.57, 0.53], [2/3 + 0.025 - next_cell, 2/3 + 0.025 - next_cell, 2/3 + 0.025 + 0.3, 2/3 + 0.025 + 0.3], color='black'))
	ax.add_line(mlines.Line2D([0.63, 0.67, 0.67, 0.63], [1/3 + 0.025 - next_cell, 1/3 + 0.025 - next_cell, 1/3 + 0.025 + 0.3 + next_cell, 1/3 + 0.025 + 0.3 + next_cell], color='black'))
	ax.add_line(mlines.Line2D([0.73, 0.77, 0.77, 0.73], [0/3 + 0.025 - next_cell, 0/3 + 0.025 - next_cell, 0/3 + 0.025 + 0.3 + next_cell, 0/3 + 0.025 + 0.3 + next_cell], color='black'))

	ax.table(cellText=[[v] for v in range(1, 6)], bbox=[0, 2/3 + 0.025, 0.45, 0.3])
	ax.table(cellText=[[v] for v in range(6, 11)], bbox=[0, 1/3 + 0.025, 0.45, 0.3])
	ax.table(cellText=[[v] for v in range(11, 16)], bbox=[0, 0 + 0.025, 0.45, 0.3])

	ax.set_xlim(0, 1)
	ax.set_ylim(0, 1)

	plt.xticks([], [])
	plt.yticks([], [])

	plt.show()
