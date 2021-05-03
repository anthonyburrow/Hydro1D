#pragma once

#include <vector>

#include "Hydro.hpp"

namespace myHydro
{
    void initDM(myHydro::Hydro &hydro);

    void initR(myHydro::Hydro &hydro);
    void initU(myHydro::Hydro &hydro);

    void initQ(myHydro::Hydro &hydro);

    void initV(myHydro::Hydro &hydro);
    void initT(myHydro::Hydro &hydro);
}