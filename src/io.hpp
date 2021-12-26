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

    void setOutputPrecision(myHydro::Hydro &hydro);
    bool fileExists(const std::string &fileName);

    void writeLESolution(myHydro::LaneEmden &laneEmden);
    void readLESolution(std::vector<double> &xData, std::vector<double> &yData,
                        const std::string &fileName);
    void writeHydrostatic();

    void writeOutput(myHydro::Hydro &hydro);
}
