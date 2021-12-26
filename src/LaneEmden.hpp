#pragma once

#include <string>

namespace myHydro
{
    class LaneEmden
    {
    public:
        const int n;
        const int maxIter;

        LaneEmden(const int &polyIndex, const double &stepSize = 0.001,
                  const int &maxIter = 10000);

        void solve(const std::string &fileName);

        void getRadius(double &r);
        void getInteriorMass(double &m);
        void getDensity(double &rho);
        void getPressure(double &P, const double &rho);

    private:
        double t;        // dimensionless diff. eq. variables
        double x;
        double dxdt;
        double dt;

        double K;        // Polytropic proportionality
        double lambda;   // radius scale
        double alpha;    // mass scale

        void calcK();
        void iterate();
    };
}
