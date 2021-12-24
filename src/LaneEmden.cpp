#include "LaneEmden.hpp"
#include "io.hpp"
#include "constants.hpp"

using namespace std;

namespace myHydro
{
    LaneEmden::LaneEmden(const int &polyIndex, const string &filename,
                         const double &stepSize, const int &maxIter)
      :
        n(polyIndex),
        maxIter(maxIter),
        outFile(filename)
    {
        if (polyIndex > 5 || 0 > polyIndex)
        {
            throw invalid_argument("Polytropic index must be between 0 and 5.");
        }

        t = myHydro::zero;
        x = 1.0;
        dxdt = myHydro::zero;
        dt = stepSize;

        calcK();
        lambda = sqrt(
            (n + 1) * K * pow(myHydro::rhoC, ((1 - n) / n)) /
            (myHydro::pi4 * myHydro::G)
        );
    }

    void LaneEmden::solve()
    {
        int iter = 0;
        while (iter < maxIter && 0.0 < x)
        {
            iterate();
            writeOutput(*this);

            iter++;
        }
    }

    void LaneEmden::getRadius(double &r)
    {
        r = lambda * t;
    }

    void LaneEmden::getDensity(double &rho)
    {
        rho = myHydro::rhoC * pow(x, n);
    }

    void LaneEmden::getPressure(double &P, const double &rho)
    {
        double K;

        switch(n)
        {
            case 3:
                K = myHydro::K3;
                break;
            default:
                K = myHydro::zero;
        }

        P = K * pow(rho, n);
    }

    void LaneEmden::calcK()
    {
        switch(n)
        {
            case 3:
                K = myHydro::K3;
                break;
            default:
                K = myHydro::zero;
        }
    }

    void LaneEmden::iterate()
    {
        dxdt = dxdt - (2.0 * dxdt / t + pow(x, n)) * dt;
        x = x + dxdt * dt;
        t = t + dt;
    }
}
