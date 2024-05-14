#include <iostream>
#include <fstream>

#include "LaneEmden.hpp"
#include "io.hpp"
#include "constants.hpp"

using namespace std;

namespace myHydro
{
    LaneEmden::LaneEmden(const int &polyIndex, const double &stepSize,
                         const int &maxIter)
      :
        n(polyIndex),
        dXi(stepSize),
        maxIter(maxIter)
    {
        if (polyIndex > 5 || 0 > polyIndex)
        {
            throw invalid_argument("Polytropic index must be between 0 and 5.");
        }

        xi = myHydro::zero;
        theta = 1.0;
        dThetaDXi = myHydro::zero;

        calcK();
        alpha = sqrt(
            (n + 1) * K * pow(myHydro::rhoC, ((1 - n) / n)) /
            (myHydro::pi4 * myHydro::G)
        );
        lambda = -myHydro::pi4 * pow(alpha, 3) * myHydro::rhoC;
    }

    void LaneEmden::solve(const string &fileName)
    {
        cout << "Calculating Lane-Emden solution..." << endl;

        ofstream outFile(fileName);

        int iter = 0;
        while (iter < maxIter && theta > 0.0)
        {
            iterate();
            writeLESolution(*this, outFile);

            iter++;
        }
    }

    void LaneEmden::getRadius(double &r)
    {
        r = alpha * xi;
    }

    void LaneEmden::getInteriorMass(double &m)
    {
        m = lambda * pow(xi, 2) * dThetaDXi;
    }

    void LaneEmden::getDensity(double &rho)
    {
        rho = myHydro::rhoC * pow(theta, n);

        if (rho < 0.0) { rho = zero; }
    }

    void LaneEmden::getPressure(double &P, const double &rho)
    {
        P = K * pow(rho, 1.0 + 1.0 / n);
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
        dThetaDXi = dThetaDXi - (2.0 * dThetaDXi / xi + pow(theta, n)) * dXi;
        theta = theta + dThetaDXi * dXi;
        xi = xi + dXi;
    }
}
