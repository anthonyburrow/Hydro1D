#include <iostream>
#include <cmath>
#include <vector>

#include "interpolate.hpp"

using namespace std;

namespace myHydro
{
    TwoPointPowerLaw::TwoPointPowerLaw(const vector<double> &x,
                                       const vector<double> &y)
    :
    a(x.size() - 1),
    b(x.size() - 1),
    xData(x.size()),
    yData(x.size())
    {
        for (int i = 0; i < a.size(); i++)
        {
            a[i] = 0.0;
            b[i] = 1.0;
        }

        xData = x;
        yData = y;
    }

    void TwoPointPowerLaw::predict(vector<double> &y, const vector<double> &x)
    {
        for (int i = 0; i < x.size(); i++)
        {
            predict(y[i], x[i]);
        }
    }

    void TwoPointPowerLaw::predict(double &y, const double &x)
    {
        if (x < xData[0] || x > xData.back())
        {
            cout << "Can't interpolate outside of bounds." << endl;
            return;
        }

        int i;
        for (i = 0; i < xData.size(); i++)
        {
            if (x < xData[i + 1]) { break; }
        }

        calcParams(i);

        y = a[i] * pow(x, -b[i]);
    }

    void TwoPointPowerLaw::calcParams(const int &index)
    {
        const double r1 = xData[index] / xData[index + 1];
        const double r2 = yData[index + 1] / yData[index];

        b[index] = log(r2) / log(r1);
        a[index] = yData[index] * pow(xData[index], b[index]);
    }
}
