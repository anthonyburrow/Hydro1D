#pragma once

#include <vector>

// #include "Hydro.hpp"

namespace myHydro
{
    class Hydro;

    struct hydroParams
    {
        int nZones;
        double initRMax;
        double nIter;
        double initDt;
    };

    hydroParams readParams();

    void setOutputPrecision(myHydro::Hydro &hydro);
    void writeOutput(myHydro::Hydro &hydro);
}
