import numpy as np


# central density, assume 10^7
rho_c = 1e7

# lambda from Caroll and Ostille, lambda = sqrt((n+1)Krho_c^((1-n)/n)/(4 pi G))
lamb = 1.98874e8

# K4_3 taken from hydro
K = 3.8468e14

# read in the results from the lane-emden calculations
data = np.loadtxt('poly3')

# xi -- dimensionless parameter used in Caroll and Ostille
xi = data[:,0][:-1]

# D -- dimensionless parameter used in Caroll and Ostille
D = data[:,1][:-1]

#change in D
dDdXI = data[:,2][:-1]

# density, rho = rho_c * D^3
rho = rho_c * D**3

# pressure P = K rho^((n+1)/n)
P = K * rho**((3+1)/3)

# radius r = lambda * xi
rad = lamb * xi

# mass enclosed -- M = 4 pi lambda^3 rho_c int_{0}^{xi}(xi'^2 * D^n dxi')
#M = (4 * 3.141592 * lamb**3 * xi**3 * D**3) / 3

# no cell centering
#fout = open('full_data.txt','w')

#fout.write('mass_enclosed, radius, density, pressure\n')

#for i in list(range(len(rho))):
#	fout.write(str(M[i])+' '+str(rad[i])+' '+str(rho[i])+' '+str(P[i])+'\n')

#fout.close()

# attempt to center cell 
#fout = open('data.txt','w')

#fout.write('mass, radius, density, pressure\n')

#for i in list(range(len(rho)-1)):
#	fout.write(str(M[i+1] - M[i])+' '+str((rad[i+1]+rad[i])/2)+' '+str((rho[i+1]+rho[i])/2)+' '+str((P[i+1]+P[i])/2)+'\n')

#fout.close()

M = -4 * np.pi * lamb**3 * rho_c * xi**2 * dDdXI

fout = open('data_cell_centered.txt','w')
fout.write('mass, radius, density, pressure\n')

for i in list(range(len(rho)-1)):
        fout.write(str(M[i+1]-M[i])+' '+str((rad[i+1]+rad[i])/2)+' '+str((rho[i+1]+rho[i])/2)+' '+str((P[i+1]+P[i])/2)+'\n')

fout.close()

