import numpy as np
import matplotlib.pyplot as plt

# central density, assume 10^7
rho_c = 1e7

# lambda from Caroll and Ostille, lambda = sqrt((n+1)Krho_c^((1-n)/n)/(4 pi G))
lamb = 1.98874e8
lamb = 2.08581e8

# K4_3 taken from hydro
K = 3.8468e14

# read in the results from the lane-emden calculations
data = np.loadtxt('newINTdata.txt')

# xi -- dimensionless parameter used in Caroll and Ostille
xi = data[:,0]

# D -- dimensionless parameter used in Caroll and Ostille
D = data[:,1]

#change in D
dDdXI = data[:,2]

# density, rho = rho_c * D^3
rho = rho_c * D**3

# pressure P = K rho^((n+1)/n)
#P = 1.1 * K * rho**((3+1)/3)

# radius r = lambda * xi
rad = lamb * xi

# mass enclosed M_3 = -4*np.pi*alpha_3**3*rho_c_3*xi_3**2*dtheta_3/M_sun
M = -4 * 3.141592 * lamb**3 * rho_c * xi**2 * dDdXI

# no cell centering
fout = open('full_data.txt','w')

fout.write('mass_enclosed, radius, density\n')#, pressure\n')

for i in list(range(len(rho))):
	fout.write(str(M[i])+' '+str(rad[i])+' '+str(rho[i])+'\n')# '+str(P[i])+'\n')

fout.close()

fout = open('data.txt','w')
fout.write('mass, radius, density\n')#, pressure\n')

for i in list(range(len(rho)-1)):
        fout.write(str(M[i+1]-M[i])+' '+str(rad[i])+' '+str((rho[i+1]+rho[i])/2)+'\n')# '+str((P[i+1]+P[i])/2)+'\n')

fout.close()

plt.plot(rad, M)
plt.ylabel('mass enclosed (g)')
plt.xlabel('radius (cm)')
plt.savefig('massVSrad.png')
plt.close()

plt.loglog(rad, M)
plt.ylabel('mass enclosed (g)')
plt.xlabel('radius (cm)')
plt.savefig('LOGmassVSrad.png')
plt.close()


plt.plot(rad, rho)
plt.ylabel('density (cgs)')
plt.xlabel('radius (cgs)')
plt.savefig('radiusVSdensity.png')
plt.close()

plt.loglog(rad, rho)
plt.ylabel('density (cgs)')
plt.xlabel('radius (cgs)')
plt.savefig('LOGradiusVSdensity.png')
plt.close()
