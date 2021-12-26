#include <iostream>

#include "io.hpp"
#include "Hydro.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    string fileName = "./config/params";
    myHydro::hydroParams params = myHydro::readParams(fileName);
    myHydro::Hydro hydro(params);

    // hydro.write();

    // cout << "Calculating each iteration..." << endl ;
    // while (hydro.iter < hydro.nIter)
    // {
    //     hydro.iterate();
    //     hydro.write();
    // }

    cout << "Complete." << endl;

    return 0;
}
