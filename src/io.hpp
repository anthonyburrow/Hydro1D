#pragma once

#include <string>
#include <vector>

// #include "Hydro.hpp"
#include "LaneEmden.hpp"

namespace myHydro
{
    class Hydro;

    struct hydroParams
    {
        int nZones;
        double initRMax;
        double totalMass;
        double nIter;
        double initDt;
        bool freeFall;
        bool resetLaneEmden;
    };

    hydroParams readParams();

    bool fileExists(const std::string &fileName);
    void readLESolution(myHydro::Hydro &hydro);

    void setOutputPrecision(myHydro::Hydro &hydro);
    void writeOutput(myHydro::Hydro &hydro);
    void writeOutput(myHydro::LaneEmden &laneEmden);
}
