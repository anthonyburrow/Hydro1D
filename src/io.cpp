#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "io.hpp"

using namespace std;

namespace mylib {

    mylib::hydroParams readParams(const string &filename) {
        cout << "Reading from parameter file: " << filename << endl;

        ifstream param_file(filename);
        string line;
        mylib::hydroParams params;

        int count = 0;
        while (getline(param_file, line)) {
            if (line[0] == '#' || line[0] == '\0') { continue; }

            stringstream iss(line);

            switch(count) {
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
        param_file.close();

        return params;
    }

}