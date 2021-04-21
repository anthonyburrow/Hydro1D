#include <iostream>
#include <vector>

#include "Hydro.hpp"
#include "constants.hpp"

using namespace std;

namespace myHydro
{
    void initR(myHydro::Hydro &hydro)
    {
        // Start with uniform spacial boundaries
        const double dR = hydro.initRMax / hydro.nZones;

        hydro.R[0] = zero;   // BC

        for (int i = 1; i < hydro.nBoundaries; i++)
        {
            hydro.R[i] = hydro.R[i - 1] + dR;
        }
    }

    void initU(myHydro::Hydro &hydro)
    {
        hydro.U[0] = zero;   // BC

        // Start from rest
        for (int i = 1; i < hydro.nBoundaries; i++)
        {
            hydro.U[i] = zero;
        }
    }

    void initQ(myHydro::Hydro &hydro)
    {
        // No pseudoviscosity at the start
        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.Q[i] = zero;
        }
    }

    void initV(myHydro::Hydro &hydro)
    {
        // initial (1 / density) profile (needs to integrate to 10 M_sol)

        // const double rhoc = 2e13;   // Central density

        // This is linear density with rho_c that integrates to 10 M_sol
        const double rhoc = 10.0 * 1.989 * 1000.0 / (pi4 * (one_third - 0.25));
        double rho;

        hydro.V[0] = 1.0 / rhoc;

        for (int i = 1; i < hydro.nZones; i++)
        {
            rho = rhoc * (1 - sqrt(hydro.R[i] / hydro.initRMax));
            hydro.V[i] = 1 / rho;
        }
    }

    void initT(myHydro::Hydro &hydro)
    {
        // initial temperature profile
        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.T[i] = zero;
        }

        hydro.Tht = hydro.T;   // Initial assumption
    }

    void initP(myHydro::Hydro &hydro)
    {
        // intitial pressure profile
        // - zero for free-fall testing
        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.P[i] = zero;
        }
    }
}