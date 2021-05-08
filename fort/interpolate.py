import numpy as np
import matplotlib.pyplot as plt
plt.switch_backend('agg')


msol = 1.989e33
rhoc = 1e7


# Read Lane-Emden output
fn = 'data_cell_centered.txt'
data = np.loadtxt(fn, skiprows=1)

data = data[:data[:, 0].argmax() + 1]   # correct for decreasing int. mass

m_int = data[:, 0]
radius = data[:, 1]
density = data[:, 2]

# Read parameters
fn = '../config/params'
with open(fn) as F:
    lines = F.read().splitlines()

lines = [l for l in lines if l]
lines = [np.float64(l) for l in lines if l[0] != '#']

n_zones = int(lines[0])
n_boundaries = n_zones + 1
total_mass = lines[2] * msol
dm = total_mass / n_zones

# Fit output
params = np.polyfit(m_int / total_mass, density / rhoc, 10)
poly = np.poly1d(params)

m_predict = np.linspace(1e-70 / total_mass, 1, n_boundaries)

output = np.zeros((n_zones, 3))
output[:, 0] = m_predict[1:] * total_mass
output[:, 2] = poly((m_predict[1:] + m_predict[:-1]) / 2) * rhoc

prev_R_cube = 0
pi4_3 = 4 * np.pi / 3
for i in range(n_zones):
    new_R_cube = prev_R_cube + dm / (output[i, 2] * pi4_3)
    output[i, 1] = np.cbrt(new_R_cube)

    prev_R_cube = new_R_cube

fn = 'hydro_input.txt'
np.savetxt(fn, output, fmt=['%.12e', '%.12e', '%.12e'])

# Plot fit
fig, ax = plt.subplots(dpi=200)

ax.plot(m_int, density, 'ko', ms=0.5)
ax.plot(m_predict * total_mass, poly(m_predict) * rhoc, 'r-')

ax.set_xlabel('interior mass (g)')
ax.set_ylabel('zone density')

ax.set_xlim(left=0)
ax.set_ylim(0, rhoc)

fn = 'rho_mass.pdf'
fig.savefig(fn, dpi=200)
