#include <iostream>
#include <string>

#include "Hydro.hpp"

#include "io.hpp"
#include "initialize.hpp"
#include "physics.hpp"
#include "constants.hpp"

using namespace std;

namespace myHydro
{
    Hydro::Hydro(const myHydro::hydroParams &params)
      : // Allocate vectors
        U(params.nZones + 1),
        R(params.nZones + 1),
        Rht(params.nZones + 1),
        V(params.nZones),
        Vprev(params.nZones),
        Vht(params.nZones),
        XM(params.nZones + 1),
        Q(params.nZones),
        Pht(params.nZones),
        Tht(params.nZones),
        ET(params.nZones),
        EV(params.nZones),
        T(params.nZones),
        P(params.nZones),

        // Output
        filedt("./output/dt.dat"),
        fileU("./output/U.dat"),
        fileR("./output/R.dat"),
        fileV("./output/V.dat"),
        // fileT("./output/T.dat"),
        fileP("./output/P.dat"),
        fileQ("./output/Q.dat")
    {
        // Parameters
        nZones = params.nZones;
        nBoundaries = nZones + 1;
        nIter = params.nIter;
        totalMass = params.totalMass * myHydro::msol;
        freeFall = params.freeFall;
        resetLaneEmden = params.resetLaneEmden;

        iter = 0;

        dt = params.initDt;
        dtht = params.initDt;   // half-time time interval

        // Setup
        myHydro::setOutputPrecision(*this);

        initialize();
    }

    void Hydro::initialize()
    {
        calcHydrostatic();

        myHydro::calcDM(*this);

        myHydro::initU(*this);

        myHydro::calcXM(*this);   // can either read or calculate

        myHydro::initQ(*this);
        myHydro::initT(*this);
        myHydro::calcP(*this);
    }

    void Hydro::calcHydrostatic()
    {
        // Create Lane Emden model
        const int n = 3;
        const string fileName = "./output/LESolution.dat";
        const bool alreadyCalculated = fileExists(fileName);

        myHydro::LaneEmden le(n, fileName);
        if (!alreadyCalculated || resetLaneEmden) { le.solve(); }

        // Interpolate LE solution
    }

    void Hydro::iterate()
    {
        myHydro::calcU(*this);
        myHydro::calcR(*this);
        myHydro::calcV(*this);

        myHydro::calcQ(*this);
        myHydro::calcPht(*this);
        myHydro::calcET(*this);
        myHydro::calcEV(*this);

        // myHydro::calcT(*this);
        myHydro::calcP(*this);

        myHydro::calcDt(*this);

        iter++;
    }

    void Hydro::write()
    {
        myHydro::writeOutput(*this);
    }
}