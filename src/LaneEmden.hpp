#pragma once

#include <string>

namespace myHydro
{
    class LaneEmden
    {
    public:
        const int n;
        const int maxIter;

        LaneEmden(const int &polyIndex = 3,
                  const double &stepSize = 0.001,
                  const int &maxIter = 10000);

        void solve(const std::string &fileName);

        void getRadius(double &r);
        void getInteriorMass(double &m);
        void getDensity(double &rho);
        void getPressure(double &P, const double &rho);

    private:
        double xi;        // dimensionless diff. eq. variables
        double theta;
        double dThetaDXi;
        const double dXi;

        double K;         // Polytropic proportionality
        double alpha;     // radius scale
        double lambda;    // mass scale

        void calcK();
        void iterate();
    };
}
