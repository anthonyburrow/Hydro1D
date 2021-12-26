#pragma once

#include <vector>

namespace myHydro
{
    class TwoPointPowerLaw
    {
    public:
        TwoPointPowerLaw::TwoPointPowerLaw(const vector<double> &xData,
                                           const vector<double> &yData);

        void predict(std::vector<double> &y, const std::vector<double> &x);
        void predict(double &y, const double &x);
    
    private:
        std::vector<double> a;
        std::vector<double> b;

        const std::vector<double> &xData;
        const std::vector<double> &yData;

        void calcParams(const int &index);
    };
}
