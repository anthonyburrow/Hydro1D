#pragma once

#include <string>
#include <vector>

#include "io.hpp"

namespace myHydro {

    class Hydro {

        public:
            const int &nZones;
            const int nBoundaries;
            int iter;
            const int &nIter;
            const double &initRMax;

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
            std::vector<double> ET;
            std::vector<double> EV;
            std::vector<double> T;
            std::vector<double> Tht;
            std::vector<double> P;

            // std::vector<double> AK;
            // std::vector<double> AL;
            // std::vector<double> sdot;

            Hydro(const string &paramFile);

            void iterate();

        private:
            const mylib::hydroParams &params;

            void initVectors();

    };

}