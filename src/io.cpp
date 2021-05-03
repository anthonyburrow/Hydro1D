#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>

#include "io.hpp"
#include "Hydro.hpp"

using namespace std;

namespace myHydro
{
    myHydro::hydroParams readParams()
    {
        string filename = "./config/params";
        cout << "Reading from parameter file: " << filename << endl;

        ifstream paramFile(filename);
        string line;
        myHydro::hydroParams params;

        int count = 0;
        while (getline(paramFile, line))
        {
            if (line[0] == '#' || line[0] == '\0') { continue; }

            stringstream iss(line);

            switch(count)
            {
                case 0 :
                    int nZones;
                    iss >> nZones;
                    params.nZones = nZones;
                    cout << "  Number of zones: " << nZones << endl;
                    break;
                case 1 :
                    double initRMax;
                    iss >> initRMax;
                    params.initRMax = initRMax;
                    cout << "  Initial radius of star: " << initRMax << endl;
                    break;
                case 2 :
                    double totalMass;
                    iss >> totalMass;
                    params.totalMass = totalMass;
                    cout << "  Total mass: " << totalMass << " m_sol" << endl;
                    break;
                case 3 :
                    double nIter;
                    iss >> nIter;
                    params.nIter = nIter;
                    cout << "  Number of time steps: " << nIter << endl;
                    break;
                case 4 :
                    double initDt;
                    iss >> initDt;
                    params.initDt = initDt;
                    cout << "  Initial dt: " << initDt << endl;
                    break;
                case 5 :
                    bool freeFall;
                    iss >> freeFall;
                    params.freeFall = freeFall;
                    cout << "  System in free-fall: ";
                    cout << boolalpha << freeFall << endl;
                    break;
                default :
                    cout << "Too many lines in param file" << endl;
            }

            count++;
        }
        paramFile.close();

        return params;
    }

    void setOutputPrecision(myHydro::Hydro &hydro)
    {
        const int n_digits = numeric_limits<double>::max_digits10;

        hydro.filedt << setprecision(n_digits);
        hydro.fileR << setprecision(n_digits);
        hydro.fileU << setprecision(n_digits);
        hydro.fileV << setprecision(n_digits);
        hydro.fileP << setprecision(n_digits);
    }

    void writeOutput(myHydro::Hydro &hydro)
    {
        hydro.filedt << hydro.dt << endl;

        for (int i = 0; i < hydro.nBoundaries; i++)
        {
            hydro.fileR << hydro.R[i] << " ";
            hydro.fileU << hydro.U[i] << " ";
        }

        for (int i = 0; i < hydro.nZones; i++)
        {
            hydro.fileV << hydro.V[i] << " ";
            hydro.fileP << hydro.P[i] << " ";
        }

        hydro.fileR << endl;
        hydro.fileU << endl;
        hydro.fileV << endl;
        hydro.fileP << endl;
    }
}