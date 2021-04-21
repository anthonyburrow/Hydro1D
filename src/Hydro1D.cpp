#include <iostream>

#include "Hydro.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    myHydro::hydroParams params = myHydro::readParams();
    myHydro::Hydro hydro(params);

    while (hydro.iter < hydro.nIter)
    {
        cout << "iter " << hydro.iter << endl;
        hydro.iterate();
    }

    // write to file

    cout << "Complete." << endl;

    return 0;
}
