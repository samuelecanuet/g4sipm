#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, glob
import matplotlib.pyplot as plt
import numpy as np
from ROOT import TFile, TTree
millivolt = 1e-9
		
if __name__ == "__main__":
	filename = glob.glob('../../results/*.root')[-1]
	if len(sys.argv) > 1:
		filename = sys.argv[1]
	# Plot range from arguments
	start = 0
	stop = 1000
	if len(sys.argv) > 3:
		start = int(sys.argv[2])
		stop = start + int(sys.argv[3])
	
	#display SiPMs signals
	fig, axs = plt.subplots(3,3, figsize=(16,9))
	# Open file.
	f = TFile(filename)
	for index in range(1,9):
		try:
			digi = f.Get(f"g4sipmVoltageTraceDigis-{index}")
			model = f.Get("sipmModel")
			model.GetEntry(0)
			# Extract trace.
			voltages = []
			times = []
			for i in range(digi.GetEntries()):
				digi.GetEntry(i)
				if digi.time >= start and digi.time <= stop:
					voltages.append(digi.voltage / millivolt)
					times.append(digi.time / 1000)

			axs[(index - 1) // 3][(index - 1) % 3].plot(times, voltages, '-')
			axs[(index - 1) // 3][(index - 1) % 3].set_ylabel('voltage / mV')
			axs[(index - 1) // 3][(index - 1) % 3].set_xlabel(u'time / µs')
			axs[(index - 1) // 3][(index - 1) % 3].set_figtitle(f"g4sipmVoltageTraceDigis-{index}")
		except:
			None
	fig.suptitle("%s\n%d x %d mm, %d $\mu$m pitch\n%d cells"  % (model.model, model.pitch, model.pitch, model.cellPitch * 1000, model.numberOfCells))
	plt.show()

