import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os
plt.switch_backend('agg')


_data_dir = './output'
_fig_dir = './doc/figs'


zone_num = 5


# R vs time
# ------------------------

fn = '%s/dt.dat' % _data_dir
data_dt = np.loadtxt(fn)
time = np.zeros(data_dt.shape)
time[1:] = data_dt[:-1].cumsum()

fn = '%s/R.dat' % _data_dir
data_R = np.loadtxt(fn, usecols=(zone_num,))

fig, ax = plt.subplots(dpi=150)

ax.plot(time[::10], data_R[::10], 'o-', color='k', markersize=1)

ax.set_xlabel('time [sec]')
ax.set_ylabel('R [cm]')

ax.set_yscale('log')

fn = '%s/R_time.pdf' % _fig_dir
fig.savefig(fn, format='pdf', dpi=150)

# P vs rho
# ------------------------

fn = '%s/V.dat' % _data_dir
data_rho = np.loadtxt(fn, usecols=(zone_num,))
data_rho = 1 / data_rho

fn = '%s/P.dat' % _data_dir
data_P = np.loadtxt(fn, usecols=(zone_num,))

fig, ax = plt.subplots(dpi=150)

ax.plot(data_rho[::10], data_P[::10], 'o-', color='k', markersize=1)

ax.set_xlabel(r'$\mathrm{\rho\ [g\ cm^{-3}]}$')
ax.set_ylabel(r'$\mathrm{P\ [dynes\ cm^{-2}]}$')

ax.set_xlim(1e4, 1e18)
ax.set_ylim(1e21, 1e40)

ax.set_xscale('log')
ax.set_yscale('log')

fn = '%s/P_rho.pdf' % _fig_dir
fig.savefig(fn, format='pdf', dpi=150)

# Velocity vs radius
# ------------------------

fn = '%s/R.dat' % _data_dir
data_R = np.loadtxt(fn)

fn = '%s/U.dat' % _data_dir
data_U = np.loadtxt(fn)

_save_dir = '%s/%s' % (_fig_dir, 'U_R')
os.makedirs(_save_dir, exist_ok=True)

n_iter = data_R.shape[0]
for i in range(0, n_iter, 100):
    fig, ax = plt.subplots()

    ax.plot(data_R[i, 1:], data_U[i, 1:], 'o-', color='k', markersize=2)

    ax.set_xlabel(r'$\mathrm{R\ [cm]}$', fontsize=18)
    ax.set_ylabel(r'$\mathrm{Velocity\ [cm\ s^{-1}]}$', fontsize=18)

    ax.set_title('t = %.6e sec' % time[i], fontsize=18)

    # ax.set_xlim(1e5, 2.95e10)
    # ax.set_ylim(-1e11, 1e10)

    ax.set_xscale('log')

    fn = '%s/U_R_%.6e.png' % (_save_dir, time[i])
    fig.savefig(fn)

    plt.close('all')


# Velocity vs radius (gif)
# ------------------------

# fig, ax = plt.subplots()

# line, = ax.plot([], [], 'o-', color='k', markersize=2)

# ax.set_xlabel(r'$\mathrm{R\ [cm]}$')
# ax.set_ylabel(r'$\mathrm{Velocity\ [cm\ s^{-1}]}$')

# ax.set_xlim(1e5, 2.95e10)
# ax.set_ylim(-1e11, 1e10)

# ax.set_xscale('log')

# title = ax.set_title('')

# def init():
#     line.set_data([], [])
#     title.set_text('')
#     return line, title

# def animate(i):
#     line.set_data(data_R[i], data_U[i])
#     title.set_text('t = %.3e sec' % time[i])
#     return line, title,

# anim = FuncAnimation(fig, animate, init_func=init,
#                      frames=range(0, n_iter, int(n_iter / 100)),
#                      interval=75, blit=True)

# fn = '%s/U_R.gif' % _save_dir
# anim.save(fn, writer='imagemagick')

plt.close('all')

# Q / P vs radius (gif)
# ------------------------

# fn = '%s/Q.dat' % _data_dir
# data_Q = np.loadtxt(fn)

# fn = '%s/P.dat' % _data_dir
# data_P = np.loadtxt(fn)

# _save_dir = '%s/%s' % (_fig_dir, 'QP_R')
# os.makedirs(_save_dir, exist_ok=True)

# fig, ax = plt.subplots()

# line, = ax.plot([], [], 'o-', color='k', markersize=2)

# ax.set_xlabel(r'$\mathrm{R\ [cm]}$')
# ax.set_ylabel(r'$\mathrm{Q\ /\ P}$')

# ax.set_xlim(1e5, 2.95e10)
# ax.set_ylim(-1e-4, 5)

# ax.set_xscale('log')

# title = ax.set_title('')

# def init():
#     line.set_data([], [])
#     title.set_text('')
#     return line, title

# def animate(i):
#     line.set_data(data_R[i, :-1], data_Q[i] / data_P[i])
#     title.set_text('t = %.4e sec' % time[i])
#     return line, title,

# anim = FuncAnimation(fig, animate, init_func=init,
#                      frames=range(0, n_iter, int(n_iter / 100)),
#                      interval=75, blit=True)

# fn = '%s/QP_R.gif' % _save_dir
# anim.save(fn, writer='imagemagick')