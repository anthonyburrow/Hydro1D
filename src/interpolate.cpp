#include <cmath>
#include "interpolate.hpp"

using namespace std;

namespace myHydro
{
    void TwoPointPowerLaw::fit(const double &x1, const double &y1,
                               const double &x2, const double &y2)
    {
        const double r1 = x1 / x2;
        const double r2 = y2 / y1;

        b = log(r2) / log(r1);
        a = y1 * pow(x1, b);
    }

    void TwoPointPowerLaw::predict(double &y, const double &x)
    {
        y = a * pow(x, -b);
    }
}
