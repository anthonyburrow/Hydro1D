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

    hydroParams readParams(const std::string &fileName);

    void setOutputPrecision(myHydro::Hydro &hydro);
    bool fileExists(const std::string &fileName);

    void writeLESolution(myHydro::LaneEmden &laneEmden,
                         std::ofstream &outFile);
    void readLESolution(std::vector<double> &mass, std::vector<double> &density,
                        const std::string &fileName);
    void writeHydrostatic(const std::vector<double> &r,
                          const std::vector<double> &m,
                          const std::vector<double> &V,
                          const std::string &fileName);

    void writeOutput(myHydro::Hydro &hydro);
}
