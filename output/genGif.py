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
u = np.empty((10001,101))
vel = np.empty((10001,100))

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
udat = open('U.dat','r')
line = udat.readline()
for i in list(range(10000)):
	u[i] = line.split()
	line = udat.readline()
vdat = open('V.dat','r')
line = vdat.readline()
for i in list(range(10000)):
	vel[i] = line.split()
	line = vdat.readline()

fig,(ax1,ax2,ax3) = plt.subplots(3,1)
ax1.set_ylabel('velocity')
ax2.set_ylabel('U')
ax3.set_ylabel('density')

ax1.set_xscale('log')
ax2.set_xscale('log')
ax3.set_xscale('log')
line1, = ax1.plot([],[],lw=2)
line2, = ax2.plot([],[],lw=2)
line3, = ax3.plot([],[],lw=2)
fig.suptitle('')

def init():
	line1.set_data([],[])
	line2.set_data([],[])
	line3.set_data([],[])
	return line1, line2, line3,

def animate(i):
	i = i * 1000
	print(i)
	x = rad[i][:-1]
	yVelo = vel[i]
	yTemp = u[i][:-1]
	yDen = rho[i]
	line1.set_data(x,yVelo)
	line2.set_data(x,yTemp)
	line3.set_data(x,yDen)
	ax1.set_title('t = '+'{:.4f}'.format(time[i])+' s')
	return line1, line2, line3,


ani = animation.FuncAnimation(fig, animate, init_func=init, frames=int(len(time)/1000),interval=80,blit=False)

print('saving it')
ani.save('hydro_movie.gif', writer='ffmpeg', fps=10)

plt.show()
plt.close()
