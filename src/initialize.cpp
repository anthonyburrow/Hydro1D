#include <iostream>
#include <vector>
#include <cmath>

#include "Hydro.hpp"
#include "constants.hpp"
#include "io.hpp"

using namespace std;

namespace myHydro
{
    void initDM(myHydro::Hydro &hydro)
    {
        // Uniform mass per zone
        hydro.DM = hydro.totalMass / hydro.nZones;
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
