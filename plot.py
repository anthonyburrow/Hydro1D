import numpy as np
import matplotlib.pyplot as plt
plt.switch_backend('agg')


_data_dir = './output'
_fig_dir = './doc/figs'


fn = '%s/dt.dat' % _data_dir
data_dt = np.loadtxt(fn)
time = np.zeros(data_dt.shape)
time[1:] = data_dt[:-1].cumsum()

fn = '%s/R.dat' % _data_dir
data_R = np.loadtxt(fn, usecols=(30,))

# R vs time
fig, ax = plt.subplots(dpi=150)

ax.plot(time, data_R, '-', color='k')

ax.set_xlabel('time [sec]')
ax.set_ylabel('R [cm]')

fn = '%s/R_time.pdf' % _fig_dir
fig.savefig(fn, format='pdf', dpi=150)
