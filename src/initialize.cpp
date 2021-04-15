#include <vector>

#include "Hydro.hpp"

using namespace std;

namespace myHydro {

    void initR(myHydro::Hydro &hydro) {
        // Start with uniform spacial boundaries
        const double dR = hydro.initRMax / hydro.nZones;

        hydro.R[0] = 0;   // BC for all time

        for (int i = 1; i < hydro.nBoundaries; i++) {
            hydro.R[i] = hydro.R[i - 1] + dR;
        }
    }

    void initU(myHydro::Hydro &hydro) {
        hydro.U[0] = 0;   // BC for all time

        // Start with zero velocities
        for (int i = 1; i < hydro.nBoundaries; i++) {
            hydro.U[i] = 0;
        }
    }

    void initP(myHydro::Hydro &hydro) {

    }

    void initV(myHydro::Hydro &hydro) {

    }

    void initT(myHydro::Hydro &hydro) {
        // stuff here

        hydro.Tht = hydro.T;
    }

}