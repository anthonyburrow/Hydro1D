import numpy as np
import matplotlib.pyplot as plt
plt.switch_backend('agg')


_data_dir = './output'
_fig_dir = './doc/figs'

zone_num = 10

fn = '%s/dt.dat' % _data_dir
data_dt = np.loadtxt(fn)
time = np.zeros(data_dt.shape)
time[1:] = data_dt[:-1].cumsum()

fn = '%s/R.dat' % _data_dir
data_R = np.loadtxt(fn, usecols=(zone_num,))

fn = '%s/V.dat' % _data_dir
data_rho = np.loadtxt(fn, usecols=(zone_num,))
data_rho = 1 / data_rho

fn = '%s/P.dat' % _data_dir
data_P = np.loadtxt(fn, usecols=(zone_num,))

# R vs time
fig, ax = plt.subplots(dpi=150)

ax.plot(time, data_R, 'o-', color='k')

ax.set_xlabel('time [sec]')
ax.set_ylabel('R [cm]')

fn = '%s/R_time.pdf' % _fig_dir
fig.savefig(fn, format='pdf', dpi=150)

# P vs rho
fig, ax = plt.subplots(dpi=150)

ax.plot(data_rho, data_P, 'o-', color='k', markersize=2)

ax.set_xlabel(r'$\mathrm{\rho\ [g\ cm^{-3}]}$')
ax.set_ylabel(r'$\mathrm{P\ [dynes\ cm^{-2}]}$')

ax.set_xscale('log')
ax.set_yscale('log')

fn = '%s/P_rho.pdf' % _fig_dir
fig.savefig(fn, format='pdf', dpi=150)
