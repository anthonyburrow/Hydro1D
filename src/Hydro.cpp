#include <string>

#include "Hydro.hpp"

#include "io.hpp"
#include "initialize.hpp"
#include "physics.hpp"

using namespace std;

namespace myHydro
{
    Hydro::Hydro(const string &paramFile)
      : params(myHydro::readParams(paramFile)),
        nZones(params.nZones),
        nBoundaries(nZones + 1),
        nIter(params.nIter),
        initRMax(params.initRMax)
    {
        iter = 0;

        dt = params.initDt;
        dtht = params.initDt;   // half-time time interval

        initVectors();
    }

    void Hydro::initVectors()
    {
        U.reserve(nBoundaries);
        myHydro::initU(*this);

        R.reserve(nBoundaries);
        Rht.reserve(nBoundaries);
        myHydro::initR(*this);

        V.reserve(nZones);
        Vprev.reserve(nZones);
        Vht.reserve(nZones);
        myHydro::initV(*this);

        // Should not change in Lagrangian frame
        DM.reserve(nZones);
        myHydro::calcDM(*this);

        // Should not change in Lagrangian frame
        DMb.reserve(nBoundaries);
        myHydro::calcDMb(*this);

        // Should not change in Lagrangian frame
        XM.reserve(nBoundaries);
        myHydro::calcXM(*this);

        Q.reserve(nZones);
        myHydro::calcQ(*this);

        Pht.reserve(nZones);
        Tht.reserve(nZones);
        ET.reserve(nZones);
        EV.reserve(nZones);

        T.reserve(nZones);
        myHydro::initT(*this);

        P.reserve(nZones);
        myHydro::initP(*this);
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

        // myHydro::calcAK(*this);
        // myHydro::calcAL(*this);
        // myHydro::calcSdot(*this);

        myHydro::calcT(*this);
        myHydro::calcP(*this);

        myHydro::calcDt(*this);

        iter++;
    }
}