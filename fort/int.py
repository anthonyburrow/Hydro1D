import matplotlib.pyplot as plt
import numpy as np
from scipy.integrate import odeint

#set up function which can solve the lame emden equation for any value of 'n'.
def solve(n):
    """Solves the Lame-Emdem equation for any value of n.
    
    args: n
    """
    #create empty lists for theta and xi values to store them into
    theta_values = []
    xi_values = []
    
    #define values of xi, delta xi, the gradient and theta
    xi = 0.00001
    d_xi = 0.001
    dtheta = 0
    theta = 1
    
    #create a variable to store xi
    xi_now = xi
    
    #use while loop to find theta and xi values until theta=0
    while (theta >= 0) and (xi_now < 20):
        
        #increase xi value by small amount
        xi_now = xi_now + d_xi
    
        #calculate values after small increase in xi
        dtheta_next = dtheta - (((2/xi_now)*dtheta)+theta**n)*d_xi
        theta_next = theta + dtheta_next*d_xi

        #update the old values to be the new ones
        dtheta = dtheta_next
        theta  = theta_next
        
        #store these values in list
        theta_values.append(theta)
        xi_values.append(xi_now)
    
    #convert lists to arrays to make it easier to deal with
    xi_values = np.array(xi_values)
    theta_values = np.array(theta_values)
    return (xi_values, theta_values)


def gradient(n):
    """Finds the gradient (dtheta/dxi) for any value of n.
    
    args: n
    """
    #create empty lists for theta, xi and dtheta values to store them into
    theta_values = []
    xi_values = []
    dtheta_values = []
    
    #define values of xi, delta xi, the gradient and theta
    xi = 0.00001
    d_xi = 0.001
    dtheta = 0
    theta = 1
    
    #create a variable to store xi
    xi_now = xi
    
    #use while loop to find theta and xi values until theta=0
    while (theta >= 0) and (xi_now < 20):
        
        #increase xi value by small amount
        xi_now = xi_now + d_xi
    
        #calculate values after small increase in xi
        dtheta_next = dtheta - (((2/xi_now)*dtheta)+theta**n)*d_xi
        theta_next = theta + dtheta_next*d_xi

        #update the old values to be the new ones
        dtheta = dtheta_next
        theta  = theta_next
        
        #store these values in list
        theta_values.append(theta)
        xi_values.append(xi_now)
        dtheta_values.append(dtheta)
    
    #convert lists to arrays to make it easier to deal with
    xi_values = np.array(xi_values)
    theta_values = np.array(theta_values)
    dtheta_values = np.array(dtheta_values)
    return (dtheta_values)

dtheta_3 = gradient(3)



#call the function to find the theata and xi values for each n
xi_3, theta_3 = solve(3)

fout = open('newINTdata.txt','w')

for i in list(range(len(xi_3))):
    fout.write(str(xi_3[i])+' '+str(theta_3[i])+' '+str(dtheta_3[i])+'\n')

fout.close()
