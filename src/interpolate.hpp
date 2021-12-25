#pragma once

namespace myHydro
{
    class TwoPointPowerLaw
    {
    public:
        double a = 0.0;
        double b = 1.0;

        void fit(const double &x1, const double &y1,
                 const double &x2, const double &y2);
        void predict(double &y, const double &x);
    };
}
