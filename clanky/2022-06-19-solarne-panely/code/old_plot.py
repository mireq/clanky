# -*- coding: utf-8 -*-
from math import pi, sin, cos
import matplotlib.pyplot as plt
import numpy as np
import sys
from datetime import datetime
from decimal import Decimal as D


# Calculations based on https://www.aa.quae.nl/en/reken/zonpositie.html

rad = pi / 180.0
j2000 = datetime(2000, 1, 1)
epoch_start_j2000 = 2451545
obliquity = rad * 23.4397 # earth obliquity

year_data_start = datetime(2000, 1, 1)


def to_j2000(dt):
	seconds = (dt - j2000).total_seconds() - (12 * 60 * 60)
	return seconds / (24 * 60 * 60)


def mean_anomaly(j2000_day):
	return ((357.5291 + (0.98560028 * j2000_day)) % 360) * rad


def equation_center(M):
	return rad * (1.9148 * np.sin(M) +  0.0200 * np.sin(M * 2) +  0.0003 * np.sin(M * 3))


def ecliptic_longitude(L):
	P = rad * 102.9372
	return (L + P + pi) % (2 * pi)


def declination(L):
	return np.arcsin(np.sin(L) * sin(obliquity))


def right_ascension(L):
	return np.arctan2(np.sin(L) * cos(obliquity), np.cos(L))


def sun_coordinates(t):
	M = mean_anomaly(t)
	C = equation_center(M)
	L = ecliptic_longitude(M + C)
	return {
		'dec': declination(L),
		'ra': right_ascension(L),
	}


def sidereal_time(d, lw):
	return rad * (280.16 + 360.9856235 * d) - lw


def azimuth(H, phi, dec):
	return np.arctan2(np.sin(H), np.cos(H) * sin(phi) - np.tan(dec) * cos(phi))


def altitude(H, phi, dec):
	return np.arcsin(sin(phi) * np.sin(dec) + cos(phi) * np.cos(dec) * np.cos(H))


def connect_close(figure=None):
	def press_key(event):
		if event.key == 'escape':
			plt.close('all')
	if not figure:
		figure = plt.gcf()
	figure.canvas.mpl_connect('key_press_event', press_key)


def test():
	lat = 49
	lon = -20.3

	phi = rad * lat
	lw = rad * (-lon)

	j2000_start = to_j2000(year_data_start)
	j2000_end = j2000_start + 1
	d = np.arange(j2000_start, j2000_end, 0.01)
	coordinates = sun_coordinates(d)
	H = sidereal_time(d, lw) - coordinates['ra']
	azim = azimuth(H, phi, coordinates['dec'])
	alt = altitude(H, phi, coordinates['dec'])
	#s = np.cos(t)
	plt.plot(d, azim / rad)
	plt.show()


TOOLS = {
	'test': test,
}


def main():
	if len(sys.argv) != 2:
		sys.stderr.write(f"Usage: {sys.argv[0]} tool")
		sys.exit(-1)
	tool = sys.argv[1]
	if tool not in TOOLS:
		sys.stderr.write(f"Unknown tools, available: " + (', '.join(TOOLS.keys())))
		sys.exit(-1)
	connect_close()
	TOOLS[tool]()


if __name__ == "__main__":
	main()


#def show_optimal_angle():
#
#	ticks_per_day = 24 * 30
#
#	day_times = np.arange(datetime(2021,1,1), datetime(2022,1,1), timedelta(seconds=86400/ticks_per_day)).astype(datetime)
#	positions = suncalc.get_position(day_times, LNG, LAT)
#
#	angles = np.arange(0, 90, 0.25)
#
#	light_intensity = get_light_intensity(positions, to_rad(angles))
#	light_intensity = sum(light_intensity[:,minute::ticks_per_day] for minute in range(ticks_per_day)) / ticks_per_day * 24
#
#	f = plt.figure(figsize=(18, 8))
#	gs = f.add_gridspec(2, 2, height_ratios=[0.05,1], width_ratios=[2, 1])
#	gs.update(left=0.05, right=0.95, bottom=0.08, top=0.93, wspace=0.0, hspace=0.02)
#	ax1 = f.add_subplot(gs[1, 0])
#	ax2 = f.add_subplot(gs[1, 1])
#	color_ax = f.add_subplot(gs[0, 0])
#	ax1.set_xlim((day_times[0], day_times[-1]))
#
#	styled_contour(ax1, color_ax, light_intensity, day_times[::ticks_per_day], angles, 20, plt.get_cmap('inferno'))
#
#	connect_close(f)
#
#	plt.show()
