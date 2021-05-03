#include <iostream>

#include "io.hpp"
#include "Hydro.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    myHydro::hydroParams params = myHydro::readParams();
    myHydro::Hydro hydro(params);

    hydro.write();

    cout << "Calculating each iteration..." << endl ;
    while (hydro.iter < hydro.nIter)
    {
        hydro.iterate();
        hydro.write();
    }

    cout << "Complete." << endl;

    return 0;
}
