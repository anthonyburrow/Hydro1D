import h5py
import numpy as np
import matplotlib.pyplot as plt
import argparse
import matplotlib.animation as animation

dt = np.genfromtxt('dt.dat')
time = []
elapsed = 0
for i in dt:
	elapsed = elapsed + i
	time.append(elapsed)
rho = np.empty((10001,100))
rad = np.empty((10001,101))
vel = np.empty((10001,101))

pdat = open('P.dat','r')
line = pdat.readline()
for i in list(range(10000)):
	rho[i] = line.split()
	line = pdat.readline()
pdat.close()
rdat = open('R.dat','r')
line = rdat.readline()
for i in list(range(10000)):
	rad[i] = line.split()
	line = rdat.readline()
vdat = open('U.dat','r')
line = vdat.readline()
for i in list(range(10000)):
	vel[i] = line.split()
	line = vdat.readline()

fig,(ax1,ax2) = plt.subplots(2,1)

ax1.set_xscale('log')
#ax1.set_yscale('log')
#ax2.set_yscale('log')
ax2.set_xscale('log')
ax1.set_xlim(1e5,1e10)
#ax1.set_ylim(-1e10,-1e7)
#ax2.set_ylim(1e-18,1e-5)
ax2.set_xlim(1e5,1e10)
line1, = ax1.plot([],[])
line2, = ax2.plot([],[])
fig.suptitle('')

n = 100

def init():
	line1.set_data([],[])
	line2.set_data([],[])
	return line1, line2,

def animate(i):
	i = i * n
	print(i)
	x = rad[i][:-1]
	yVelo = vel[i][:-1]
	yDen = rho[i]
	line1.set_data(x,yVelo)
	line2.set_data(x,yDen)
	ax1.set_title('t = '+'{:.4f}'.format(time[i])+' s')
	return line1, line2,


ani = animation.FuncAnimation(fig, animate, init_func=init, frames=int(len(time)/n),interval=80,blit=False)

print('saving it')
ani.save('hydro_movie.mp4', writer='ffmpeg', fps=10)

plt.show()
plt.close()
