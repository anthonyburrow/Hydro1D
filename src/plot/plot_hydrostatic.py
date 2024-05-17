import numpy as np
import matplotlib.pyplot as plt
plt.switch_backend('agg')


_data_dir = './output'
_fig_dir = './doc/figs'


fn = '%s/LESolution.dat' % _data_dir
data_le = np.loadtxt(fn)
mass_le = data_le[:, 1]
rho_le = data_le[:, 2]

fn = '%s/Hydrostatic.dat' % _data_dir
data_interp = np.loadtxt(fn)
mass_interp = data_interp[:, 1]
rho_interp = data_interp[:, 2]

fig, ax = plt.subplots(dpi=150)

ax.plot(mass_le, rho_le, 'o-', color='k', markersize=2, label='LE Solution')
ax.plot(mass_interp, rho_interp, 'o-', color='r', markersize=2, label='interpolation')

ax.set_xlabel(r'$\mathrm{interior\ mass\ [M_\odot]}$')
ax.set_ylabel(r'$\mathrm{\rho\ [M_\odot\ R_\odot^{-3}]}$')

# ax.set_xscale('log')
# ax.set_yscale('log')

ax.legend()

fn = '%s/hydrostatic_m_rho.pdf' % _fig_dir
fig.savefig(fn, format='pdf', dpi=150)


