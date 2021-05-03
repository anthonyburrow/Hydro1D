#include <vector>
#include <cmath>
#include <iostream>

#include <iomanip>

#include "Hydro.hpp"
#include "physics.hpp"
#include "constants.hpp"

using namespace std;

namespace myHydro
{
    void calcXM(myHydro::Hydro &hydro)
    {
        hydro.XM[0] = myHydro::zero;   // BC

        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.XM[i + 1] = hydro.XM[i] + hydro.DM;
        }
        // cout << hydro.XM[hydro.nZones] / 1.989e33 << " m_sol" << endl;
    }

    void calcR(myHydro::Hydro &hydro)
    {
        double newR;

        for (int i = 1; i < hydro.nBoundaries; i++)
        {
            newR = hydro.R[i] + hydro.U[i] * hydro.dtht;

            hydro.Rht[i] = 0.5 * (hydro.R[i] + newR);

            hydro.R[i] = newR;
        }
    }

    void calcU(myHydro::Hydro &hydro)
    {
        double R_sq;
        double dP;
        double dQ;
        const int &nZones = hydro.nZones;

        for (int i = 1; i < nZones; i++)
        {
            R_sq = pow(hydro.R[i], 2);
            dP = hydro.P[i] - hydro.P[i - 1];   // P at each boundary
            dQ = hydro.Q[i] - hydro.Q[i - 1];   // Q at each boundary

            hydro.U[i] = hydro.U[i] -
                         hydro.dt *
                             (myHydro::pi4_sq * R_sq * (dP + dQ) / hydro.DM
                             + myHydro::G * hydro.XM[i] / R_sq);
        }

        // Outer boundary with dP = dQ = 0
        R_sq = pow(hydro.R[nZones], 2);
        hydro.U[nZones] = hydro.U[nZones] -
                          hydro.dt * myHydro::G * hydro.XM[nZones] / R_sq;
    }

    void calcV(myHydro::Hydro &hydro)
    {
        double RCube = myHydro::zero;
        double nextRCube;

        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.Vprev[i] = hydro.V[i];

            nextRCube = pow(hydro.R[i + 1], 3);
            hydro.V[i] = myHydro::pi4_3 * (nextRCube - RCube) / hydro.DM;
            RCube = nextRCube;

            hydro.Vht[i] = 0.5 * (hydro.V[i] + hydro.Vprev[i]);
        }
    }

    void calcQ(myHydro::Hydro &hydro)
    {
        double dU;

        for (int i = 0; i < hydro.nZones; i++)
        {
            dU = hydro.U[i + 1] - hydro.U[i];

            if (hydro.V[i] < hydro.Vprev[i] && dU < 0)
            {
                hydro.Q[i] = 2.0 * pow(dU, 2) / hydro.Vht[i];
            }
            else { hydro.Q[i] = myHydro::zero; }
 
        }
    }

    void calcPht(myHydro::Hydro &hydro)
    {
        for (int i = 0; i < hydro.nZones; i++)
        {
            if (hydro.freeFall)
            {
                hydro.Pht[i] = myHydro::zero;
            }
            else
            {
                polytropicEoS(hydro.Pht[i], hydro.Tht[i], hydro.Vht[i]);
            }
        }
    }

    void calcET(myHydro::Hydro &hydro)
    {
        // ETht as a function of Tht, Vht
        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.ET[i] = myHydro::zero;
        }
    }

    void calcEV(myHydro::Hydro &hydro)
    {
        // EVht as a function of Tht, Vht
        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.EV[i] = myHydro::zero;
        }
    }

    void calcT(myHydro::Hydro &hydro)
    {
        double prevT;

        for (int i = 0; i < hydro.nZones; i++)
        {
            // // Calc T
            prevT = hydro.T[i];

            hydro.T[i] = hydro.T[i]
                         // Hydro terms
                         - (hydro.V[i] - hydro.Vprev[i])
                               * (hydro.P[i] + hydro.Q[i] + hydro.EV[i])
                               / hydro.ET[i];

            // Calc Tht
            hydro.Tht[i] = 1.5 * hydro.T[i] - 0.5 * prevT;
        }
    }

    void calcP(myHydro::Hydro &hydro)
    {
        for (int i = 0; i < hydro.nZones; i++)
        {
            if (hydro.freeFall)
            {
                hydro.P[i] = myHydro::zero;
            }
            else
            {
                polytropicEoS(hydro.P[i], hydro.T[i], hydro.V[i]);
            }
        }
    }

    void polytropicEoS(double &P, const double &T, const double &V)
    {
        const double rho = 1 / V;

        // Assume star made up of relativistic fermions (gamma = 4/3)
        const double Pelectron = myHydro::K4_3 * pow(rho, myHydro::four_thirds);

        if (rho < myHydro::rhoNuc)
        {
            // Only electron degeneracy
            P = Pelectron;
        }
        else
        {
            // Assume "stiff" gamma = 2 for nuclear degeneracy, plus the
            //    electron degeneracy term
            P = Pelectron + myHydro::K2 * pow(rho, 2.0);
        }
    }

    void calcDt(myHydro::Hydro &hydro)
    {
        // Update dt for stability
        double newDtht = myHydro::zero;
        double tmpDt;

        for (int i = 0; i < hydro.nZones; i++)
        {
            tmpDt = 0.02 * hydro.V[i] * hydro.dtht /
                        abs(hydro.V[i] - hydro.Vprev[i]);
            
            if (i == 0 || tmpDt < newDtht) { newDtht = tmpDt; }
        }

        hydro.dt = 0.5 * (hydro.dtht + newDtht);
        hydro.dthtPrev = hydro.dtht;
        hydro.dtht = newDtht;
    }
}