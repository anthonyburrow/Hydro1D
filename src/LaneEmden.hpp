#pragma once

#include <fstream>

namespace myHydro
{
    class LaneEmden
    {
    public:
        const int n;
        const int maxIter;
        std::ofstream outFile;

        LaneEmden(const int &polyIndex, const std::string &file,
                  const double &stepSize = 0.001, const int &maxIter = 10000);

        void solve();

        void getRadius(double &r);
        void getDensity(double &rho);
        void getPressure(double &P, const double &rho);

    private:
        double t;        // dimensionless diff. eq. variables
        double x;
        double dxdt;
        double dt;

        double K;        // Polytropic proportionality
        double lambda;   // radius scale

        void calcK();
        void iterate();
    };
}
