#include <iostream>

#include "Hydro.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    string inFilename = "./config/params";

    myHydro::Hydro hydro(inFilename);

    int count = 0;
    while (count < hydro.nIter)
    {
        hydro.iterate();
        count++;
    }

    // write to file

    cout << "Complete." << endl;

    return 0;
}
