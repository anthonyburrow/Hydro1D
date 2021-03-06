#pragma once

#include <vector>

#include "Hydro.hpp"

namespace myHydro
{
    void calcDM(myHydro::Hydro &hydro);
    void calcXM(myHydro::Hydro &hydro);

    void calcR(myHydro::Hydro &hydro);
    void calcU(myHydro::Hydro &hydro);
    void calcV(myHydro::Hydro &hydro);

    void calcQ(myHydro::Hydro &hydro);
    void calcPht(myHydro::Hydro &hydro);
    void calcET(myHydro::Hydro &hydro);
    void calcEV(myHydro::Hydro &hydro);

    void calcT(myHydro::Hydro &hydro);
    void calcP(myHydro::Hydro &hydro);

    void polytropicEoS(double &P, const double &T, const double &V);

    void calcDt(myHydro::Hydro &hydro);
}