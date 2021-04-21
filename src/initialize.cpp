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

        hydro.R[0] = 0;   // BC

        for (int i = 1; i < hydro.nBoundaries; i++)
        {
            hydro.R[i] = hydro.R[i - 1] + dR;
        }
    }

    void initU(myHydro::Hydro &hydro)
    {
        hydro.U[0] = 0;   // BC

        // Start from rest
        for (int i = 1; i < hydro.nBoundaries; i++)
        {
            hydro.U[i] = 0;
        }
    }

    void initV(myHydro::Hydro &hydro)
    {
        // initial (1 / density) profile
        const double rhoc = 2e-14;   // Central density
        double rho;

        hydro.V[0] = 1 / rhoc;

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