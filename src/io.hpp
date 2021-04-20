#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace mylib {

    struct hydroParams {
        int nZones;
        double initRMax;
        double nIter;
        double initDt;
    };

    hydroParams readParams(const std::string &filename);

}