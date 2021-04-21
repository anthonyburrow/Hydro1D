#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "io.hpp"

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
                    double nIter;
                    iss >> nIter;
                    params.nIter = nIter;
                    cout << "  Number of time steps: " << nIter << endl;
                    break;
                case 3 :
                    double initDt;
                    iss >> initDt;
                    params.initDt = initDt;
                    cout << "  Initial dt: " << initDt << endl;
                    break;
                default :
                    cout << "Too many lines in param file" << endl;
            }

            count++;
        }
        paramFile.close();

        return params;
    }
}