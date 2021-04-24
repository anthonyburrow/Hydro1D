#include <iostream>

#include "io.hpp"
#include "Hydro.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    myHydro::hydroParams params = myHydro::readParams();
    myHydro::Hydro hydro(params);

    hydro.write();

    while (hydro.iter < hydro.nIter)
    {
        // cout << "iter " << hydro.iter << endl;
        hydro.iterate();
        hydro.write();
    }

    cout << "Complete." << endl;

    return 0;
}
