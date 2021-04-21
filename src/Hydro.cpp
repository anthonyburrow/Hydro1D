#include <iostream>
#include <string>

#include "Hydro.hpp"

#include "io.hpp"
#include "initialize.hpp"
#include "physics.hpp"

using namespace std;

namespace myHydro
{
    Hydro::Hydro(const myHydro::hydroParams &params)
      : U(params.nZones + 1),
        R(params.nZones + 1),
        Rht(params.nZones + 1),
        V(params.nZones),
        Vprev(params.nZones),
        Vht(params.nZones),
        DM(params.nZones),
        DMb(params.nZones + 1),
        XM(params.nZones + 1),
        Q(params.nZones),
        Pht(params.nZones),
        Tht(params.nZones),
        ET(params.nZones),
        EV(params.nZones),
        T(params.nZones),
        P(params.nZones)
    {
        nZones = params.nZones;        
        nBoundaries = nZones + 1;        
        nIter = params.nIter;        
        initRMax = params.initRMax;        

        dt = params.initDt;
        dtht = params.initDt;   // half-time time interval

        iter = 0;

        initVectors();
    }

    void Hydro::initVectors()
    {
        myHydro::initU(*this);
        myHydro::initR(*this);
        myHydro::initV(*this);

        myHydro::calcDM(*this);
        myHydro::calcDMb(*this);
        myHydro::calcXM(*this);

        myHydro::initQ(*this);
        myHydro::initT(*this);
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