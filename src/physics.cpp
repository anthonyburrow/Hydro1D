#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>

#include "Hydro.hpp"

using namespace std;

const double pi4 = 4 * M_PI;
const double pi4_sq = pi4 * pi4;
const double pi4_3 = pi4 / 3;
const double one_third = 1 / 3;

// Newton gravitation constant
const double G = 132709742648;   // km^3 Msol^-1 s^-2
// Radiation constant
const double a = 7.5657e-15;   // erg cm^-3 K^-4
// Speed of light
const double c = 2.99792458e10;   // cm s^-1

namespace myHydro {

    void calcDM(myHydro::Hydro &hydro) {
        double RCube = 0;
        double nextRCube;

        for (int i = 0; i < hydro.nBoundaries; i++) {
            nextRCube = pow(hydro.R[i + 1], 3);
            hydro.DM[i] = pi4_3 * (nextRCube - RCube) / hydro.V[i];
            RCube = nextRCube;
        }
    }

    void calcDMb(myHydro::Hydro &hydro) {
        hydro.DMb[0] = hydro.DM[0];   // BC

        for (int i = 1; i < hydro.nZones; i++) {
            hydro.DMb[i] = 0.5 * (hydro.DM[i] + hydro.DM[i - 1]);
        }

        hydro.DMb[hydro.nZones] = hydro.DM[hydro.nZones - 1];
    }

    void calcXM(myHydro::Hydro &hydro) {
        hydro.XM[0] = 0;   // BC

        for (int i = 1; i < hydro.nBoundaries; i++) {
            hydro.XM[i + 1] = hydro.XM[i] + hydro.DM[i];
        }
    }

    void calcR(myHydro::Hydro &hydro) {
        double newR;

        for (int i = 1; i < hydro.nBoundaries; i++) {
            newR = hydro.R[i] + hydro.U[i] * hydro.dt;

            hydro.Rht[i] = 0.5 * (hydro.R[i] + newR);

            hydro.R[i] = newR;
        }
    }

    void calcU(myHydro::Hydro &hydro) {
        double R_sq;
        double dP;
        double dQ;
        const int &nZones = hydro.nZones;
        
        for (int i = 1; i < nZones; i++) {
            R_sq = pow(hydro.R[i], 2);
            dP = hydro.P[i] - hydro.P[i - 1];   // P at the boundary
            dQ = hydro.Q[i] - hydro.Q[i - 1];   // Q at the boundary

            hydro.U[i] = hydro.U[i] +
                         hydro.dt * (pi4_sq * R_sq * (dP + dQ) / hydro.DMb[i] -
                                     G * hydro.XM[i] / R_sq);
        }

        // Outer boundary with dP = dQ = 0
        R_sq = pow(hydro.R[nZones], 2);
        hydro.U[nZones] = hydro.U[nZones] -
                          hydro.dt * G * hydro.XM[nZones] / R_sq;
    }

    void calcV(myHydro::Hydro &hydro) {
        double RCube = 0;
        double nextRCube;

        for (int i = 0; i < hydro.nZones; i++) {
            hydro.Vprev[i] = hydro.V[i];

            nextRCube = pow(hydro.R[i + 1], 3);
            hydro.V[i] = pi4_3 * (nextRCube - RCube) / hydro.DM[i];
            RCube = nextRCube;

            hydro.Vht[i] = 0.5 * (hydro.V[i] + hydro.Vprev[i]);
        }
    }

    void calcQ(myHydro::Hydro &hydro) {
        double dU;

        for (int i = 0; i < hydro.nZones; i++) {
            dU = hydro.U[i + 1] - hydro.U[i];

            if (hydro.V[i] < hydro.Vprev[i] && dU < 0) {
                hydro.Q[i] = 2 * pow(dU, 2) / hydro.Vht[i];
            }
            else { hydro.Q[i] = 0; }
 
        }
    }

    void calcPht(myHydro::Hydro &hydro) {
        // Pht as a function of Tht, Vht
    }

    void calcET(myHydro::Hydro &hydro) {
        // ETht as a function of Tht, Vht
    }

    void calcEV(myHydro::Hydro &hydro) {
        // EVht as a function of Tht, Vht
    }

    void calcAK(myHydro::Hydro &hydro) {
        // AK as a function of Tht, Vht
    }

    void calcAL(myHydro::Hydro &hydro) {
        double prevT4 = pow(hydro.Tht[0], 4);
        double nextT4;
        double prevDM_AK = hydro.DM[0] * hydro.AK[0];
        double nextDM_AK;

        hydro.AL[0] = 0;   // BC

        for (int i = 1; i < hydro.nZones; i++) {
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

    void calcSdot(myHydro::Hydro &hydro) {
        // Not sure
    }

    void calcT(myHydro::Hydro &hydro) {
        double prevT;

        for (int i = 0; i < hydro.nZones; i++) {
            // Calc T
            prevT = hydro.T[i];

            hydro.T[i] = hydro.T[i] + (
                             // Radiation terms
                             hydro.dt * (
                                 hydro.sdot[i] -
                                 (hydro.AL[i + 1] - hydro.AL[i]) / hydro.DM[i]
                             ) -
                             // Hydro terms
                             (hydro.V[i] - hydro.Vprev[i]) * (
                                 hydro.P[i] + hydro.Q[i] + hydro.EV[i]
                             )
                         ) / hydro.ET[i];

            // Calc Tht
            // When dt is not constant, this equation needs
            // to be slightly different
            hydro.Tht[i] = 1.5 * hydro.T[i] - 0.5 * prevT;
        }
    }

    void calcP(myHydro::Hydro &hydro) {
        // P as a function of T, V
    }

}