#include <iostream>
#include <vector>
#include <cmath>

#include "Hydro.hpp"
#include "constants.hpp"

using namespace std;

namespace myHydro
{
    void initDM(myHydro::Hydro &hydro)
    {
        // Uniform mass per zone
        hydro.DM = hydro.totalMass / hydro.nZones;
    }

    void initR(myHydro::Hydro &hydro)
    {
        // Give zones equal mass
        double prevRCube = myHydro::zero;
        double newRCube;

        hydro.R[0] = myHydro::zero;   // BC

        for (int i = 0; i < hydro.nZones; i++)
        {
            newRCube = prevRCube + hydro.DM * hydro.V[i] / myHydro::pi4_3;

            hydro.R[i + 1] = cbrt(newRCube);

            prevRCube = newRCube;
        }
    }

    void initU(myHydro::Hydro &hydro)
    {
        hydro.U[0] = myHydro::zero;   // BC

        // Start from rest
        for (int i = 1; i < hydro.nBoundaries; i++)
        {
            hydro.U[i] = myHydro::zero;
        }
    }

    void initQ(myHydro::Hydro &hydro)
    {
        // No pseudoviscosity at the start
        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.Q[i] = myHydro::zero;
        }
    }

    void initV(myHydro::Hydro &hydro)
    {
        // initial (1 / density) profile (needs to integrate to 10 M_sol)
        double rho;

        // hydro.V[0] = 1.0 / myHydro::rhoc;

        // TODO: Read in density values
        for (int i = 1; i < hydro.nZones; i++)
        {
            rho = myHydro::rhoc * (1 - hydro.R[i] / hydro.initRMax);
            hydro.V[i] = 1.0 / rho;
        }
    }

    void initT(myHydro::Hydro &hydro)
    {
        // initial temperature profile
        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.T[i] = myHydro::zero;
        }

        hydro.Tht = hydro.T;   // Initial assumption
    }

}