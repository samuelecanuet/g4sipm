#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, glob
import matplotlib.pyplot as plt
import numpy as np
from ROOT import TFile, TTree

import seaborn as sns


custom_params = {
        "xtick.direction" : "out",
        "ytick.direction" : "out",
        "lines.markeredgecolor" : "k",
        "lines.markeredgewidth" : 0.5,
        "lines.linewidth" : 1,
        "lines.markersize" : 5,
        "figure.figsize" : (9,9),
        "font.family" : "serif",
        "ytick.labelsize" : 10,
        "xtick.labelsize" : 10,
        "axes.labelsize" : 10,
        "axes.titlesize" : 10,
        "legend.fontsize" : 10,
        "text.usetex" : True,
        # 'figure.subplot.left': 0.20, 
        # 'figure.subplot.bottom': 0.15, 
        # 'figure.subplot.right': 0.95, 
        # 'figure.subplot.top': 0.90
        }
sns.set_theme(style="ticks", rc=custom_params)

	
if __name__ == "__main__":
	filename = glob.glob('../../results/*.root')[-1]
	if len(sys.argv) > 1:
		filename = sys.argv[1]
	# Plot range from arguments
	start = 0
	stop = 10000
	if len(sys.argv) > 3:
		start = int(sys.argv[2])
		stop = start + int(sys.argv[3])
	
	#display SiPMs signals
	fig, axs = plt.subplots(3,3, figsize=(9,9))
	# Open file.
	f = TFile(filename)
	print(filename)
	Nb_event=0
	for i in f.GetListOfKeys():
		if i.GetName() == "g4sipmHits-1":
			Nb_event+=1
	
	for index in range(1,10):
		for event in range(1,Nb_event+1):	
			digi = f.Get(f"g4sipmVoltageTraceDigis-{index};{event}")
			model = f.Get("sipmModel")
			hit = f.Get(f"g4sipmHits-{index};{event}").GetEntries()
			model.GetEntry(0)
			# Extract trace.
			voltages = []
			times = []
			for i in range(digi.GetEntries()):
				digi.GetEntry(i)
				if digi.time >= start and digi.time <= stop:
					voltages.append(digi.voltage )
					times.append(digi.time / 1000)
			axs[(index - 1) // 3][(index - 1) % 3].plot(times, voltages, '-')
			axs[(index - 1) // 3][(index - 1) % 3].set_title(f"SiPM n°{index}")
			axs[(index - 1) // 3][(index - 1) % 3].label_outer()
			axs[(index - 1) // 3][(index - 1) % 3].text(0.1, 0.9, f"Hits : {hit}", transform=axs[(index - 1) // 3][(index - 1) % 3].transAxes)

			if (index - 1) // 3 == 2:
				axs[(index - 1) // 3][(index - 1) % 3].set_xlabel(u'time / µs')
			if (index - 1) % 3 == 0:
				axs[(index - 1) // 3][(index - 1) % 3].set_ylabel("Voltage (mV)")

	fig.suptitle("%s\n%d x %d mm, %d $\mu$m pitch\n%d cells"  % (model.model, model.pitch, model.pitch, model.cellPitch * 1000, model.numberOfCells))
	plt.show()


	# fig, axs = plt.subplots(3,3, figsize=(9,9), sharex='all', sharey='all')
	# plt.subplots_adjust(wspace=0.3, hspace=0.3)
	
	# for index in range(1,10):
	# 	hit = f.Get(f"g4sipmHits-{index}")
	# 	liste_x=[]
	# 	liste_y=[]
	# 	for i in range(hit.GetEntries()):
	# 		hit.GetEntry(i)
	# 		liste_x.append(hit.position[0])
	# 		liste_y.append(hit.position[1])

	# 	x_offset = ((index - 1) // 3-1) * 6.75
	# 	y_offset = ((index - 1) % 3-1) * 6.75
	# 	axs[(index - 1) // 3][(index - 1) % 3].hist2d(np.array(liste_x)-x_offset, np.array(liste_y)-y_offset, bins=(150, 150))
	# 	axs[(index - 1) // 3][(index - 1) % 3].set_title(f"SiPM n°{index}")
	# 	axs[(index - 1) // 3][(index - 1) % 3].label_outer()

	# 	if (index - 1) // 3 == 2:
	# 		axs[(index - 1) // 3][(index - 1) % 3].set_xlabel("x (mm)")
	# 	if (index - 1) % 3 == 0:
	# 		axs[(index - 1) // 3][(index - 1) % 3].set_ylabel("y (mm)")

	# fig.suptitle("%s\n%d x %d mm, %d $\mu$m pitch\n%d cells"  % (model.model, model.pitch, model.pitch, model.cellPitch * 1000, model.numberOfCells))
	# plt.show()

