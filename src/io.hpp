#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace myHydro
{
    struct hydroParams
    {
        int nZones;
        double initRMax;
        double nIter;
        double initDt;
    };

    hydroParams readParams();
}
