import numpy as np


# read in the results from the lane-emden calculations
#   xi    -- dimensionless parameter used in Caroll and Ostille
#   D     -- dimensionless parameter used in Caroll and Ostille
#   dDdXI -- change in D
data = np.loadtxt('./output/poly3')[:-1]

xi = data[:, 0]
D = data[:, 1]
dDdXI = data[:, 2]

n = 3
G = 6.6743e-8
msol = 1.989e33

# Read total mass
fn = './config/params'
with open(fn) as F:
    lines = F.read().splitlines()

lines = [l for l in lines if l]
lines = [np.float64(l) for l in lines if l[0] != '#']

M = lines[1] * msol

# central density, assume 10^7
rho_c = 1e7

# Calculate constant K for given total mass M
K = M / (-4 * np.pi * xi[-1]**2 * dDdXI[-1])
K = K**(2 / 3)
K *= 4 * np.pi * G / (n + 1)
print('  K = %.5e' % K)

# lambda from Caroll and Ostille, lambda = sqrt((n+1)Krho_c^((1-n)/n)/(4 pi G))
# lamb = 1.98874e8
lamb = np.sqrt((n + 1) * K * rho_c**((1 - n) / n) / (4 * np.pi * G))

# density, rho = rho_c * D^3
rho = rho_c * D**3

# pressure P = K rho^((n+1)/n)
P = K * rho**((n + 1) / n)

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

fout = open('./output/data_cell_centered.txt', 'w')
fout.write('mass, radius, density, pressure\n')

for i in list(range(len(rho)-1)):
        fout.write(str(M[i])+' '+str((rad[i+1]+rad[i])/2)+' '+str((rho[i+1]+rho[i])/2)+' '+str((P[i+1]+P[i])/2)+'\n')

fout.close()
