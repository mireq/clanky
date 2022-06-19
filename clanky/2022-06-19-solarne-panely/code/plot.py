# -*- coding: utf-8 -*-
import sys
from datetime import datetime, timedelta

import math
import matplotlib.dates
import matplotlib.colors
import numpy as np
import sympy
import json
import scipy.signal
from matplotlib import pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvas
from matplotlib.cm import ScalarMappable
from matplotlib.figure import Figure
from scipy.ndimage import gaussian_filter
from suncalc import suncalc


LAT = 49
LNG = 20.3
SYMPY_RAD = sympy.pi / 180

TARGET_TEMPERATURE = 16.0 # cieľová teplota
LIGHT_TEMPERATURE_INCREASE = 30.0 # zvýšenie teploty pri maximálnej intenzite kolmo na povrch
HEAT_TRANSFER_COEFFICIENT = 1800 # 1/1800°C za jednu minútu pri rozdiele 1°C
OPTIMAL_ANGLE = 48.7

TOTAL_HEAT_ENERGY = 32317
TOTAL_ELECTRICITY_ENERGY = 1550


def get_sympy_model(substiture_coordinates=True):
	obliquity = SYMPY_RAD * 23.4397

	day_symbol = sympy.symbols('day')
	day = day_symbol - 0.5

	mean_anomally = SYMPY_RAD * (357.5291 + 0.98560028 * day)

	center = SYMPY_RAD * (1.9148 * sympy.sin(mean_anomally) + 0.02 * sympy.sin(2 * mean_anomally) + 0.0003 * sympy.sin(3 * mean_anomally))
	perihelion = SYMPY_RAD * 102.9372
	ecliptic_longitude = mean_anomally + center + perihelion + sympy.pi

	def declination(l):
		return sympy.asin(sympy.sin(obliquity) * sympy.sin(l))

	def right_ascension(l):
		return sympy.atan2(sympy.sin(l) * sympy.cos(obliquity), sympy.cos(l))

	def sidereal_time(d, lw):
		return SYMPY_RAD * (280.16 + 360.9856235 * d) - lw

	def altitude(s_time, phi, dec):
		return sympy.asin(sympy.sin(phi) * sympy.sin(dec) + sympy.cos(phi) * sympy.cos(dec) * sympy.cos(s_time))

	def azimuth(s_time, phi, dec):
		return sympy.atan2(sympy.sin(s_time), sympy.cos(s_time) * sympy.sin(phi) - sympy.tan(dec) * sympy.cos(phi))

	dec = declination(ecliptic_longitude)
	ra = right_ascension(ecliptic_longitude)

	lw = (-SYMPY_RAD) * sympy.symbols('longitude')
	phi = SYMPY_RAD * sympy.symbols('latitude')

	if substiture_coordinates:
		lw = lw.subs({'longitude': LNG})
		phi = phi.subs({'latitude': LAT})

	sidereal_time_value = sidereal_time(day, lw) - ra
	altitude_value = altitude(sidereal_time_value, phi, dec)
	azimuth_value = azimuth(sidereal_time_value, phi, dec)

	return {
		'dec': dec,
		'ra': ra,
		'altitude': altitude_value,
		'azimuth': azimuth_value,
		'day': day_symbol,
	}


def show_sympy_declination():
	model = get_sympy_model()
	start_day = suncalc.to_days(datetime(2000, 1, 1))
	end_day = suncalc.to_days(datetime(2001, 1, 1))

	sympy.plot(
		model['dec'] / SYMPY_RAD,
		(model['day'], start_day, end_day),
		axis_center=(start_day, 0.0),
		xlabel='Deň',
		ylabel='Uhol'
	)


def show_sympy_altitude():
	model = get_sympy_model()
	start_day = suncalc.to_days(datetime(2000, 1, 1))
	end_day = suncalc.to_days(datetime(2000, 1, 2))

	sympy.plot(
		model['altitude'] / SYMPY_RAD,
		(model['day'], start_day, end_day),
		axis_center=(start_day, 0.0),
		xlabel='Deň',
		ylabel='Uhol',
		adaptive=False,
		nb_of_points=1440
	)


def sympy_intensity_for_angle(angle, model):
	to_surface_angle = sympy.acos(
		sympy.sin(angle*SYMPY_RAD) * sympy.sin(model['altitude']) +
		sympy.cos(angle*SYMPY_RAD) * sympy.cos(model['altitude']) * sympy.cos(0 - model['azimuth'])
	)

	intensity = sympy.cos(to_surface_angle)
	intensity = sympy.Piecewise((0, intensity < 0), (0, model['altitude'] < 0), (intensity, True))
	return intensity


def show_sympy_one_day_intensity():
	model = get_sympy_model()
	start_day = suncalc.to_days(datetime(2000, 3, 1)) + 0.5
	end_day = suncalc.to_days(datetime(2000, 3, 2)) + 0.5

	plot = sympy.plot(
		sympy_intensity_for_angle(90, model),
		(model['day'], start_day, end_day),
		axis_center=(start_day, 0.0),
		xlabel='Deň',
		ylabel='Intenzita',
		adaptive=False,
		nb_of_points=1440,
		show=False
	)
	plot.append(sympy.plot(
		sympy_intensity_for_angle(0, model),
		(model['day'], start_day, end_day),
		axis_center=(start_day, 0.0),
		xlabel='Deň',
		ylabel='Intenzita',
		adaptive=False,
		nb_of_points=1440,
		show=False
	)[0])
	plot.show()


def show_sympy_year_intensity():
	model = get_sympy_model()
	start_day = suncalc.to_days(datetime(2000, 1, 1)) + 0.5
	end_day = suncalc.to_days(datetime(2001, 1, 1)) + 0.5

	plot = sympy.plot(
		sympy_intensity_for_angle(90, model),
		(model['day'], start_day, end_day),
		axis_center=(start_day, 0.0),
		xlabel='Deň',
		ylabel='Intenzita',
		adaptive=False,
		nb_of_points=366 * 48,
		show=False
	)
	plot.show()


def to_rad(angle):
	return angle * suncalc.rad


def to_angle(rad):
	return rad / suncalc.rad


def calc_angle_size(position, altitude, azimuth):
	return np.arccos(
		np.outer(np.sin(altitude), np.sin(position['altitude'])) +
		np.outer(np.cos(altitude), np.cos(position['altitude'])) * np.cos(azimuth - position['azimuth'])
	)


def get_light_intensity(sun_position, declination):
	angle_size = calc_angle_size(sun_position, declination, 0)
	light = np.cos(angle_size)
	light[:,sun_position['altitude'] < 0] = 0
	light[light < 0] = 0
	return light


def show_energy_mix():
	connect_close()

	fig = matplotlib.pyplot.gcf()
	fig.set_size_inches(10, 2)

	ax = plt.subplot(1, 1, 1)

	ax.barh([0], [TOTAL_HEAT_ENERGY], color="tab:red")
	ax.barh([1], [TOTAL_ELECTRICITY_ENERGY], color="tab:blue")
	ax.set_ylim(-1, 2)
	ax.invert_yaxis()
	ax.set_yticks([0, 1], labels=['Teplo', 'Elektrická energia'])
	ax.set_xlabel("Ročná spotreba (kWh)")


	plt.tight_layout()
	plt.show()


def show_day_altitude():
	connect_close()

	# Výpočet pre najkratší deň
	day_times = np.arange(datetime(2021,12,21), datetime(2021, 12, 22), timedelta(seconds=60)).astype(datetime) # pre každú minútu v najkratší deň
	short_positions = suncalc.get_position(day_times, LNG, LAT) # výpočet polohy

	# Výpočet pre najdlhší deň
	day_times = np.arange(datetime(2021,6,21), datetime(2021, 6, 22), timedelta(seconds=60)).astype(datetime)
	long_positions = suncalc.get_position(day_times, LNG, LAT)

	# Prevod času na hodiny
	hours = [val.total_seconds() / 3600 for val in day_times - datetime(2021,6,21)] # prevod na hodiny

	ax = plt.subplot(1, 1, 1)

	max_idx = np.argmax(long_positions['altitude']) # index with max value
	max_time = hours[max_idx]

	ax.plot(hours, to_angle(short_positions['altitude']), color='tab:blue', label="21. 12. 2021")
	ax.plot(hours, to_angle(long_positions['altitude']), color='tab:red', label="21. 6. 2021")

	ax.spines['left'].set_position(('data', max_time))
	ax.spines['left'].set_position(('data', max_time))
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)

	ax.annotate(
		'21. 12. 2021',
		xy=(max_time + 1, short_positions['altitude'][max_idx] / suncalc.rad),
		xycoords='data',
		xytext=(10, 0),
		textcoords='offset points',
		horizontalalignment='left',
		verticalalignment='top',
		color='tab:blue'
	)
	ax.annotate(
		'21. 6. 2021',
		xy=(max_time + 1, long_positions['altitude'][max_idx] / suncalc.rad),
		xycoords='data',
		xytext=(0, 0),
		textcoords='offset points',
		horizontalalignment='left',
		verticalalignment='top',
		color='tab:red'
	)

	plt.ylim((0, 90))
	plt.xlim((1, 21))
	plt.xticks(np.arange(1, 21, 1.0))
	plt.tight_layout()
	plt.show()



def get_shmu_sun_max():
	with open('data/sun_max.json', 'r') as fp:
		return np.array(json.load(fp))


def get_shmu_sun_avg():
	with open('data/sun_avg.json', 'r') as fp:
		return np.array(json.load(fp))


def get_shmu_sun_fraction():
	return get_shmu_sun_avg() / get_shmu_sun_max()


def show_year_average_duration():
	days = np.arange(datetime(2021,1,1), datetime(2022,1,1), timedelta(1)).astype(datetime)
	xticks = [datetime(2021, 3, 20), datetime(2021, 6, 21), datetime(2021, 9, 23), datetime(2021, 12, 21)]
	xticks_labels = ["Jar", "Leto", "Jeseň", "Zima"]

	sun_max = get_shmu_sun_max()
	sun_avg = get_shmu_sun_avg()
	sun_avg = scipy.signal.savgol_filter(sun_avg, 20, 2)
	sun_fraction = sun_avg / sun_max
	sun_fraction = scipy.signal.savgol_filter(sun_fraction, 20, 2)

	f = plt.figure()
	gs = f.add_gridspec(2, 1, hspace=0, wspace=0)
	(ax1, ax2) = gs.subplots(sharex='col', sharey='row')
	connect_close(f)

	ax1.plot(days, sun_max, '--', color='lightgray', label="Astronomické maximum")
	ax1.plot(days, sun_avg, color='tab:blue', label="Priemerné trvanie")
	ax1.set_ylim((0, 17))
	ax1.set_xlim((days[0], days[-1]))
	ax1.spines['top'].set_visible(False)
	ax1.spines['right'].set_visible(False)
	ax1.spines['bottom'].set_visible(False)
	ax1.grid(linestyle='dotted', color='lightgray')
	ax1.set_xticks(xticks)
	ax1.set_yticks(np.arange(0, 17, 3))
	ax1.set_title("Trvanie slnečného svitu")
	ax1.set_ylabel("Dĺžka (h)")
	ax1.legend()

	ax2.plot(days, sun_fraction * 100, color="tab:red")
	ax2.set_ylim((20, 65))
	ax2.set_yticks(np.arange(20, 70, 10))
	ax2.spines['right'].set_visible(False)
	ax2.set_xticklabels(xticks_labels)
	ax2.grid(linestyle='dotted', color='lightgray')
	ax2.set_ylabel("Podiel voči maximu (%)")

	plt.tight_layout()
	plt.show()


def show_daily_effective_intensity():
	connect_close()

	day_times = np.arange(datetime(2021,1,1), datetime(2022,1,1), timedelta(seconds=60)).astype(datetime)
	positions = suncalc.get_position(day_times, LNG, LAT)
	samples_per_day = 60 * 24

	angles = np.arange(0, 95, 5)
	cmap = plt.get_cmap('gist_rainbow')

	light_intensity = get_light_intensity(positions, to_rad(angles))

	ax = plt.subplot(1, 1, 1)
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.set_yticks(np.arange(0, 11, 1))
	ax.grid(linestyle='dotted', color='lightgray', axis='y')

	for i, angle in enumerate(angles):
		light_hours = [np.trapz(light_intensity[i][d*samples_per_day:(d+1)*samples_per_day], day_times[d*samples_per_day:(d+1)*samples_per_day]).total_seconds() / 3600 for d in range(365)]
		label = None
		if i % 3 == 0:
			label = f'{angle} °'
		ax.plot(day_times[::samples_per_day], light_hours, label=label, color=cmap(i / len(angles)))

	ax.set_ylim((0, 10))
	ax.set_xlim((day_times[0], day_times[-1]))
	ax.legend()

	plt.tight_layout()
	plt.show()


def drop_shadow(data, l0, l1, sigma=5, alpha=0.5, dpi_divisor=90):
	fig = Figure(figsize=(data.shape[1] / dpi_divisor, data.shape[0] / dpi_divisor))
	canvas = FigureCanvas(fig)
	ax = fig.add_axes([0, 0, 1, 1], frameon=False)
	ax.contourf(
		data,
		vmin=data.min(),
		vmax=data.max(),
		levels=[l0, l1],
		origin='lower',
		colors='black',
		extent=[-1, 1, -1, 1],
	)
	ax.set_xlim(-1, 1), ax.set_ylim(-1, 1)
	canvas.draw()
	A = np.array(canvas.renderer.buffer_rgba())[:, :, 0]
	del fig
	A = gaussian_filter(A, sigma)
	A = (A - A.min()) / (A.max() - A.min())
	I = np.zeros((A.shape[0], A.shape[1], 4))
	I[:, :, 3] = (1 - A) * alpha
	return I


def styled_contour(ax, data, levels, x, y, cmap, colorbar_label=None):
	d_min = np.min(levels)
	d_max = np.max(levels)

	zorder = 0
	z_icrement = 1
	contour = None
	for i in range(len(levels) - 1):
		l0, l1 = levels[i], levels[i + 1]
		zorder += z_icrement

		for sigma, alpha in [(1, 0.08), (2, 0.1), (4, 0.1), (8, 0.1), (16, 0.15)]:
			shadow = drop_shadow(data, l0, l1, sigma=sigma, dpi_divisor=20, alpha=alpha)
			ax.imshow(shadow, origin='upper', zorder=zorder, aspect='auto', extent=[matplotlib.dates.date2num(x.min()), matplotlib.dates.date2num(x.max()), y.min(), y.max()])

		contour = ax.contourf(
			x,
			y,
			data,
			vmin=d_min,
			vmax=d_max,
			levels=[l0, l1],
			origin='lower',
			cmap=cmap,
			zorder=zorder,
		)
		zorder += z_icrement

	plt.colorbar(ScalarMappable(norm=contour.norm, cmap=contour.cmap), pad=0.01, label=colorbar_label)


def show_daily_effective_intensity_2d():
	p = plt.rcParams
	p['figure.dpi'] = 150

	connect_close()

	ticks_per_day = 60 * 24 * 12
	day_times = np.arange(datetime(2021,1,1), datetime(2022,1,1), timedelta(seconds=86400/ticks_per_day)).astype(datetime)
	positions = suncalc.get_position(day_times, LNG, LAT)
	angles = np.arange(0, 91, 1)
	light_intensity = get_light_intensity(positions, to_rad(angles))
	light_intensity = sum(light_intensity[:,minute::ticks_per_day] for minute in range(ticks_per_day)) / ticks_per_day * 24

	fig = plt.gcf()
	ax = fig.add_axes([0.06, 0.05, 0.95, 0.92])
	ax.yaxis.set_major_formatter('{x:.0f}°')

	levels = np.arange(math.floor(np.min(light_intensity) * 3) / 3, np.max(light_intensity) + 0.5, 1/3)

	styled_contour(ax, light_intensity, levels, day_times[::ticks_per_day], angles, plt.get_cmap('inferno'), colorbar_label="Efektívna intenzita (h)")

	plt.show()


def show_optimal_angle():
	connect_close()

	p = plt.rcParams
	p["lines.marker"] = "o"
	p["lines.markeredgewidth"] = 1.5
	p["lines.markeredgecolor"] = "auto"
	p["lines.markerfacecolor"] = "white"
	p["lines.markersize"] = 6

	# výpočet s presnosťou na minútu
	ticks_per_day = 60 * 24 * 1
	day_times = np.arange(datetime(2021,1,1), datetime(2022,1,1), timedelta(seconds=86400/ticks_per_day)).astype(datetime)

	positions = suncalc.get_position(day_times, LNG, LAT)
	angles = np.arange(0, 90.1, 0.1)

	# výpočet teoretickej intenzity pre každý deň
	light_intensity = get_light_intensity(positions, to_rad(angles))
	light_intensity = sum(light_intensity[:,minute::ticks_per_day] for minute in range(ticks_per_day)) / ticks_per_day * 24

	# výpočet reálnej intenzity podľa dát z shmu
	real_light_intensity = light_intensity * get_shmu_sun_fraction()

	# súčet intenzity pre každý deň
	light_intensity = np.sum(light_intensity, axis=1)
	real_light_intensity = np.sum(real_light_intensity, axis=1)

	# výpočet teoretického maxima
	max_idx = np.argmax(light_intensity)
	max_angle = angles[max_idx]
	max_value = light_intensity[max_idx]

	# výpočet reálneho maxima
	real_max_idx = np.argmax(real_light_intensity)
	real_max_angle = angles[real_max_idx]
	real_max_value = real_light_intensity[real_max_idx]

	print(f"Teoreticky: uhol: {max_angle:.1f}, svetlo: {max_value:.0f}h")
	print(f"Reálne: uhol: {real_max_angle:.1f}, svetlo: {real_max_value:.0f}h")

	ax = plt.subplot(1, 1, 1)
	ax.plot(angles, light_intensity, color='tab:blue', markevery=[max_idx], label="Teoretická dĺžka svitu")
	ax.plot(angles, real_light_intensity, color='tab:red', markevery=[real_max_idx], label="Reálna dĺžka svitu (z SHMU)")
	ax.set_xlim(0, 90)
	ax.set_ylim(0, 3000)
	ax.set_xlabel("Náklon (°)")
	ax.set_ylabel("Počet efektívnych hodín slnečného svitu ročne")

	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.grid(linestyle='dotted', color='lightgray')
	ax.legend()

	ax.annotate(
		f'{max_angle:.1f}°, {max_value:.0f}h',
		xy=(max_angle, max_value),
		xycoords='data',
		xytext=(5, 20),
		textcoords='offset points',
		horizontalalignment='left',
		verticalalignment='top',
		color='tab:blue',
	)
	ax.annotate(
		f'{real_max_angle:.1f}°, {real_max_value:.0f}h',
		xy=(real_max_angle, real_max_value),
		xycoords='data',
		xytext=(5, 20),
		textcoords='offset points',
		horizontalalignment='left',
		verticalalignment='top',
		color='tab:red',
	)

	plt.tight_layout()
	plt.show()


def get_shmu_lonterm_min():
	with open('data/longterm_min_temp.json', 'r') as fp:
		return np.array(json.load(fp))


def get_shmu_lonterm_max():
	with open('data/longterm_max_temp.json', 'r') as fp:
		return np.array(json.load(fp))


def get_outside_temperature(days=365, start=0):
	ticks_per_day = 60 * 24 * 1 # pre každú minútu

	# maximálna a minimálna teplota z SHMU (obmedzená na 5 dní)
	longterm_min = get_shmu_lonterm_min()[start:start+days]
	longterm_max = get_shmu_lonterm_max()[start:start+days]

	date_start = datetime(2021,1,1) + timedelta(start)
	date_end = date_start + timedelta(days)

	# dni a rozšírené dni s rozlíšením na minútu
	whole_days = np.arange(date_start, date_end, timedelta(seconds=86400))
	day_times = np.arange(date_start, date_end, timedelta(seconds=86400/ticks_per_day))

	# interpolácia minimálnej a maximálnej teploty na minútu
	longterm_min = np.interp(day_times.astype(np.float64), whole_days.astype(np.float64), longterm_min)
	longterm_max = np.interp(day_times.astype(np.float64), whole_days.astype(np.float64), longterm_max)
	intensity_fraction = np.interp(day_times.astype(np.float64), whole_days.astype(np.float64), get_shmu_sun_fraction()[start:start+days])

	# generovanie sínusu pre každý deň s hodnotami 0, 1 a maximom o 12:00
	sin_wave = (np.sin(day_times.astype(np.float64) / 1000000 / 86400 * math.pi * 2 - math.pi / 2) + 1) / 2

	# denné teploty pomocou sínusu
	day_temperature = longterm_min + (longterm_max - longterm_min) * sin_wave

	return {
		'longterm_max': longterm_max,
		'longterm_min': longterm_min,
		'intensity_fraction': intensity_fraction,
		'day_temperature': day_temperature,
		'day_times': day_times,
		'days': whole_days,
	}


def simulate_energy_required(outside_temperature_data):
	day_times, days = outside_temperature_data['day_times'], outside_temperature_data['days']

	# výpočet intenzity svetla na povrch s nulovým sklonom
	positions = suncalc.get_position(day_times.astype(datetime), LNG, LAT)
	light_intensity = get_light_intensity(positions, to_rad(90))[0]

	# simulácia zmeny vnútornej teploty
	def simulate_indoor(accumulated, value):
		# termostat nastavuje cieľovú teplotu
		if accumulated < TARGET_TEMPERATURE:
			accumulated = TARGET_TEMPERATURE
		accumulated = accumulated + (value - accumulated) / HEAT_TRANSFER_COEFFICIENT
		return accumulated
	simulate_indoor = np.frompyfunc(simulate_indoor, 2, 1)

	# vonkajšia teplota spočítaná ako priemerná teplota + intenzita svetla
	# vynásobená zvýšením teploty (dáta z SHMU)
	outdoor_temperature = outside_temperature_data['day_temperature'] + light_intensity * LIGHT_TEMPERATURE_INCREASE * outside_temperature_data['intensity_fraction']
	# simulácia vnútornej teploty
	indoor_temperature = simulate_indoor.accumulate(outdoor_temperature)
	# ak je teplota pod cieľovou teplotou, znamená to, že bez termostatu by
	# teplota poklesla za minútu o rozdiel teploty - TARGET_TEMPERATURE
	# Energia potrebná na opätovné ohriatie je rovná rozdielu teplôt
	energy_required = (TARGET_TEMPERATURE - indoor_temperature) * HEAT_TRANSFER_COEFFICIENT
	energy_required[0] = 0 # zahadzujem prvý údaj
	energy_required[energy_required < 0] = 0

	return {
		'outdoor_temperature': outdoor_temperature,
		'indoor_temperature': indoor_temperature,
		'energy_required': energy_required,
	}


def show_outside_temperature():
	connect_close()

	data = get_outside_temperature(days=5)
	longterm_min = data['longterm_min']
	longterm_max = data['longterm_max']
	day_temperature = data['day_temperature']
	day_times = data['day_times']
	days = data['days']

	ax = plt.subplot(1, 1, 1)

	ax.plot(day_times, longterm_min, color='tab:blue', label="Dlhodobé minimum")
	ax.plot(day_times, longterm_max, color='tab:red', label="Dlhodobé maximum")
	ax.plot(day_times, day_temperature, color='tab:orange', label="Interpolovaná teplota")

	ax.set_ylabel("Teplota (°C)")
	ax.axhline(0, color='black')
	ax.set_xlim((day_times[0], day_times[-1]))
	ax.set_ylim((-9.5, 0.5))
	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.grid(linestyle='dotted', color='lightgray')

	ax.legend()

	plt.xticks(days)

	plt.tight_layout()
	plt.show()


def show_daily_heating_energy():
	connect_close()

	data = get_outside_temperature(days=6, start=140) # začiatok 20. máj
	day_times, days = data['day_times'], data['days']

	simulation = simulate_energy_required(data)
	outdoor_temperature, indoor_temperature, energy_required = simulation['outdoor_temperature'], simulation['indoor_temperature'], simulation['energy_required']

	ax = plt.subplot(1, 1, 1)
	ax.set_xlim((day_times[0], day_times[-24*60]))
	ax.set_xticks(days)
	ax.plot(day_times, data['day_temperature'], color='lightblue', label="Vonkajšia teplota")
	ax.plot(day_times, indoor_temperature, color='tab:red', label="Vnútorná teplota")
	ax.plot(day_times, energy_required, color='tab:orange', label="Energia potrebná na udržanie teploty")
	ax.set_ylabel("Teplota (°C)")

	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.grid(linestyle='dotted', color='lightgray')
	ax.legend()

	plt.tight_layout()
	plt.show()


def show_year_heating_energy():
	connect_close()

	ticks_per_day = 60 * 24 * 1

	data = get_outside_temperature(days=365, start=0)
	day_times, days = data['day_times'], data['days']

	simulation = simulate_energy_required(data)
	energy_required = simulation['energy_required']
	energy_required = sum(energy_required[minute::ticks_per_day] for minute in range(ticks_per_day))
	energy_required = energy_required / np.sum(energy_required)

	sun_fraction = scipy.signal.savgol_filter(get_shmu_sun_fraction(), 8, 2)

	positions = suncalc.get_position(day_times.astype(datetime), LNG, LAT)
	light_intensity = get_light_intensity(positions, to_rad(OPTIMAL_ANGLE))[0]
	light_intensity = sum(light_intensity[minute::ticks_per_day] for minute in range(ticks_per_day)) * sun_fraction
	light_intensity = light_intensity / np.sum(light_intensity)

	ax = plt.subplot(1, 1, 1)
	ax.set_xlim((days[0], days[-1]))
	ax.set_ylim((0, np.max(energy_required) * 1.05))
	ax2 = ax.twinx()
	ax2.set_ylim((0, np.max(light_intensity) * 1.05))

	ax.plot(days, energy_required, color='tab:red', label="Potrebná energia")
	ax2.plot(days, light_intensity, color='tab:blue', label="Slnečná energia")

	lines, labels = ax.get_legend_handles_labels()
	lines2, labels2 = ax2.get_legend_handles_labels()
	ax2.legend(lines + lines2, labels + labels2, loc='lower left')

	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.spines['left'].set_visible(False)
	ax.tick_params(axis='y', left=False, labelleft=False)
	ax.grid(linestyle='dotted', color='lightgray', axis='x')
	ax2.spines['top'].set_visible(False)
	ax2.spines['right'].set_visible(False)
	ax2.spines['left'].set_visible(False)
	ax2.tick_params(axis='y', right=False, labelright=False)

	plt.tight_layout()
	plt.show()


def show_energy():
	connect_close()

	ticks_per_day = 60 * 24 * 1

	data = get_outside_temperature(days=365, start=0)
	day_times, days = data['day_times'], data['days']

	simulation = simulate_energy_required(data)
	energy_required = simulation['energy_required']
	energy_required = sum(energy_required[minute::ticks_per_day] for minute in range(ticks_per_day))
	energy_required = energy_required / np.sum(energy_required)

	sun_fraction = scipy.signal.savgol_filter(get_shmu_sun_fraction(), 8, 2)

	positions = suncalc.get_position(day_times.astype(datetime), LNG, LAT)
	energy_produced = get_light_intensity(positions, to_rad(OPTIMAL_ANGLE))[0]
	energy_produced = sum(energy_produced[minute::ticks_per_day] for minute in range(ticks_per_day)) / np.average(sun_fraction)
	energy_produced = energy_produced / np.sum(energy_produced)

	energy_required = energy_required * TOTAL_HEAT_ENERGY + (TOTAL_ELECTRICITY_ENERGY / 365)
	energy_produced = energy_produced * (TOTAL_HEAT_ENERGY + TOTAL_ELECTRICITY_ENERGY)

	print(f"Najväčší prebytok: {np.max(energy_produced / energy_required):.2f}")
	print(f"Najväčší nedostatok: {np.max(energy_required / energy_produced):.2f}")

	sum_energy_required = np.cumsum(energy_required)
	sum_energy_produced = np.cumsum(energy_produced)
	energy_storage = sum_energy_produced - sum_energy_required
	energy_storage -= np.min(energy_storage)

	print(f"Maximálna uložená energia: {np.max(energy_storage):.0f} kWh")

	ax = plt.subplot(1, 1, 1)
	ax.set_xlim((days[0], days[-1]))

	#ax.set_ylim((0, np.max(energy_required) * 1.05))
	#ax.plot(days, energy_required, color='tab:red', label="Potrebná energia")
	#ax.plot(days, energy_produced, color='tab:blue', label="Slnečná energia")
	#ax.set_ylabel("Denná spotreba (kWh)")

	ax.set_ylim((0, np.max(energy_storage) * 1.05))
	ax.plot(days, energy_storage, color='tab:red', label="Potrebná energia")

	ax.spines['top'].set_visible(False)
	ax.spines['right'].set_visible(False)
	ax.grid(linestyle='dotted', color='lightgray')
	ax.set_ylabel("Uložená energia (kWh)")

	plt.tight_layout()
	plt.show()




TOOLS = {
	'show_sympy_declination': show_sympy_declination,
	'show_sympy_altitude': show_sympy_altitude,
	'show_sympy_one_day_intensity': show_sympy_one_day_intensity,
	'show_sympy_year_intensity': show_sympy_year_intensity,
	'show_energy_mix': show_energy_mix,
	'show_day_altitude': show_day_altitude,
	'show_year_average_duration': show_year_average_duration,
	'show_daily_effective_intensity': show_daily_effective_intensity,
	'show_daily_effective_intensity_2d': show_daily_effective_intensity_2d,
	'show_optimal_angle': show_optimal_angle,
	'show_outside_temperature': show_outside_temperature,
	'show_daily_heating_energy': show_daily_heating_energy,
	'show_year_heating_energy': show_year_heating_energy,
	'show_energy': show_energy,
}


def connect_close(figure=None):
	def press_key(event):
		if event.key == 'escape':
			plt.close('all')
	if not figure:
		figure = plt.gcf()
	figure.canvas.mpl_connect('key_press_event', press_key)


def main():
	if len(sys.argv) < 2:
		sys.stderr.write(f"Usage: {sys.argv[0]} tool")
		sys.exit(-1)
	tool = sys.argv[1]
	if tool not in TOOLS:
		sys.stderr.write(f"Unknown tools, available: " + (', '.join(TOOLS.keys())))
		sys.exit(-1)
	TOOLS[tool](*sys.argv[2:])


if __name__ == "__main__":
	main()
