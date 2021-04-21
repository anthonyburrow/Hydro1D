#include <vector>
#include <cmath>

#include "Hydro.hpp"
#include "constants.hpp"

using namespace std;

namespace myHydro
{
    void calcDM(myHydro::Hydro &hydro)
    {
        double RCube = zero;
        double nextRCube;

        for (int i = 0; i < hydro.nBoundaries; i++)
        {
            nextRCube = pow(hydro.R[i + 1], 3);
            hydro.DM[i] = pi4_3 * (nextRCube - RCube) / hydro.V[i];
            RCube = nextRCube;
        }
    }

    void calcDMb(myHydro::Hydro &hydro)
    {
        hydro.DMb[0] = hydro.DM[0];   // BC

        for (int i = 1; i < hydro.nZones; i++)
        {
            hydro.DMb[i] = 0.5 * (hydro.DM[i] + hydro.DM[i - 1]);
        }

        hydro.DMb[hydro.nZones] = hydro.DM[hydro.nZones - 1];
    }

    void calcXM(myHydro::Hydro &hydro)
    {
        hydro.XM[0] = zero;   // BC

        for (int i = 1; i < hydro.nBoundaries; i++)
        {
            hydro.XM[i + 1] = hydro.XM[i] + hydro.DM[i];
        }
    }

    void calcR(myHydro::Hydro &hydro)
    {
        double newR;

        for (int i = 1; i < hydro.nBoundaries; i++)
        {
            newR = hydro.R[i] + hydro.U[i] * hydro.dt;

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

            hydro.U[i] = hydro.U[i] +
                         hydro.dt * (pi4_sq * R_sq * (dP + dQ) / hydro.DMb[i] -
                                     G * hydro.XM[i] / R_sq);
        }

        // Outer boundary with dP = dQ = 0
        R_sq = pow(hydro.R[nZones], 2);
        hydro.U[nZones] = hydro.U[nZones] -
                          hydro.dt * G * hydro.XM[nZones] / R_sq;
    }

    void calcV(myHydro::Hydro &hydro)
    {
        double RCube = zero;
        double nextRCube;

        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.Vprev[i] = hydro.V[i];

            nextRCube = pow(hydro.R[i + 1], 3);
            hydro.V[i] = pi4_3 * (nextRCube - RCube) / hydro.DM[i];
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
                hydro.Q[i] = 2 * pow(dU, 2) / hydro.Vht[i];
            }
            else { hydro.Q[i] = 0; }
 
        }
    }

    void calcPht(myHydro::Hydro &hydro)
    {
        // Pht as a function of Tht, Vht
        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.Pht[i] = zero;
        }
    }

    void calcET(myHydro::Hydro &hydro)
    {
        // ETht as a function of Tht, Vht
        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.ET[i] = zero;
        }
    }

    void calcEV(myHydro::Hydro &hydro)
    {
        // EVht as a function of Tht, Vht
        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.EV[i] = zero;
        }
    }

    void calcT(myHydro::Hydro &hydro)
    {
        double prevT;

        for (int i = 0; i < hydro.nZones; i++)
        {
            // Calc T
            prevT = hydro.T[i];

            hydro.T[i] = hydro.T[i] + (
                             // Radiation terms
                            //  hydro.dt * (
                            //      hydro.sdot[i] -
                            //      (hydro.AL[i + 1] - hydro.AL[i]) / hydro.DM[i]
                            //  )
                             // Hydro terms
                             -(hydro.V[i] - hydro.Vprev[i]) * (
                                 hydro.P[i] + hydro.Q[i] + hydro.EV[i]
                             )
                         ) / hydro.ET[i];

            // Calc Tht
            hydro.Tht[i] = 1.5 * hydro.T[i] - 0.5 * prevT;
        }
    }

    void calcP(myHydro::Hydro &hydro)
    {
        // P as a function of T, V
    }

    void calcDt(myHydro::Hydro &hydro)
    {
        // Update dt for stability
        double newDtht = zero;
        double tmpDt;

        for (int i = 0; i < hydro.nZones; i++)
        {
            tmpDt = 0.02 * hydro.V[i] * hydro.dtht /
                        abs(hydro.V[i] - hydro.Vprev[i]);
            
            if (i = 0 || tmpDt < newDtht) { newDtht = tmpDt; }
        }

        hydro.dt = 0.5 * (hydro.dtht + newDtht);
        hydro.dthtPrev = hydro.dtht;
        hydro.dtht = newDtht;
    }

/*  Radiation
    void calcAK(myHydro::Hydro &hydro)
    {
        // AK as a function of Tht, Vht
    }

    void calcAL(myHydro::Hydro &hydro)
    {
        double prevT4 = pow(hydro.Tht[0], 4);
        double nextT4;
        double prevDM_AK = hydro.DM[0] * hydro.AK[0];
        double nextDM_AK;

        hydro.AL[0] = zero;   // BC

        for (int i = 1; i < hydro.nZones; i++)
        {
            nextT4 = pow(hydro.Tht[i], 4);
            nextDM_AK = hydro.DM[i] * hydro.AK[i];

            hydro.AL[i] = pi4_sq * a * c * one_third * pow(hydro.Rht[i], 4) *
                          2 * (nextT4 - prevT4) / (nextDM_AK + prevDM_AK);
            
            prevT4 = nextT4;
            prevDM_AK = nextDM_AK;
        }

        // Outer boundary?
        // hydro.AL[nZones] = 
    }

    void calcSdot(myHydro::Hydro &hydro)
    {
        // Not sure
    }
*/
}