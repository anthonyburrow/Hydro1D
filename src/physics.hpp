#pragma once

#include <vector>

#include "Hydro.hpp"

namespace myHydro
{
    void calcDM(myHydro::Hydro &hydro);
    void calcDMb(myHydro::Hydro &hydro);
    void calcXM(myHydro::Hydro &hydro);

    void calcR(myHydro::Hydro &hydro);
    void calcU(myHydro::Hydro &hydro);
    void calcV(myHydro::Hydro &hydro);

    void calcQ(myHydro::Hydro &hydro);
    void calcPht(myHydro::Hydro &hydro);
    void calcET(myHydro::Hydro &hydro);
    void calcEV(myHydro::Hydro &hydro);

    // void calcAK(myHydro::Hydro &hydro);
    // void calcAL(myHydro::Hydro &hydro);
    // void calcSdot(myHydro::Hydro &hydro);

    void calcT(myHydro::Hydro &hydro);
    void calcP(myHydro::Hydro &hydro);

    void calcDt(myHydro::Hydro &hydro);
}