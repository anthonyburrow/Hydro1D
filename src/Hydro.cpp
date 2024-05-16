#include <iostream>
#include <string>

#include "Hydro.hpp"

#include "io.hpp"
#include "initialize.hpp"
#include "physics.hpp"
#include "constants.hpp"
#include "interpolate.hpp"

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
        totalMass = params.totalMass * msol;
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
        myHydro::calcDM(*this);
        myHydro::calcXM(*this);
        calcHydrostatic();

        myHydro::initU(*this);

        myHydro::initQ(*this);
        myHydro::initT(*this);
        myHydro::calcP(*this);
    }

    void Hydro::calcHydrostatic()
    {
        // Create Lane Emden model
        const string inFileName = "./output/LESolution.dat";
        const bool alreadyCalculated = fileExists(inFileName);

        myHydro::LaneEmden laneEmden;
        if (!alreadyCalculated || resetLaneEmden) {
            laneEmden.solve(inFileName);
        }

        // Interpolate LE solution to get density
        vector<double> mass, density;
        readLESolution(mass, density, inFileName);
        for (int i = 0; i < mass.size(); i++) { mass[i] /= msol; }

        TwoPointPowerLaw interp(mass, density);

        vector<double> massPredict(V.size());
        for (int i = 0; i < massPredict.size(); i++)
        {
            massPredict[i] = 0.5 * (XM[i] + XM[i + 1]) / msol;
        }
        interp.predict(V, massPredict);
        for (int i = 0; i < massPredict.size(); i++) { massPredict[i] *= msol; }

        double prevRCube = 0.0;
        double newRCube;
        R[0] = 0.0;
        for (int i = 0; i < V.size(); i++)
        {
            V[i] = 1.0 / V[i];   // transform density to specific volume

            newRCube = prevRCube + DM * V[i] / pi4_3;
            R[i + 1] = cbrt(newRCube);

            prevRCube = newRCube;
        }

        const string outFileName = "./output/Hydrostatic.dat";
        writeHydrostatic(R, massPredict, V, outFileName);
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