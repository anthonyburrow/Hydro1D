#pragma once

#include <string>
#include <vector>

#include "io.hpp"

namespace myHydro
{
    class Hydro
    {
    public:
        // can't make these const references for an annoying reason :(
        int nZones;
        int nBoundaries;
        int nIter;
        double initRMax;

        int iter;
        double dt;
        double dtht;
        double dthtPrev;   // Previous dt calculation

        // Physical quantities
        //   b -> boundary alternative
        //   ht -> half-time alternative
        std::vector<double> DM;
        std::vector<double> DMb;
        std::vector<double> XM;

        std::vector<double> U;
        std::vector<double> R;
        std::vector<double> Rht;
        std::vector<double> V;
        std::vector<double> Vprev;   // Previous V calculation
        std::vector<double> Vht;

        std::vector<double> Q;
        std::vector<double> Tht;
        std::vector<double> Pht;
        std::vector<double> ET;
        std::vector<double> EV;
        std::vector<double> T;
        std::vector<double> P;

        // std::vector<double> AK;
        // std::vector<double> AL;
        // std::vector<double> sdot;

        Hydro(const myHydro::hydroParams &params);

        void iterate();

    private:
        void initVectors();
    };
}