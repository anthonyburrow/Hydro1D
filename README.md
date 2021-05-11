# Hydro1D

A simple 1D hydrocode that models the shock dynamics of a core-collapse
supernova. Developed by Anthony Burrow and Sarah Stangl.

## Loaded Schooner modules

* GCCcore/9.3.0
* zlib/1.2.11-GCCcore-9.3.0
* binutils/2.34-GCCcore-9.3.0
* iccifort/2020.1.217
* impi/2019.7.217-iccifort-2020.1.217
* iimpi/2020a
* imkl/2020.1.217-iimpi-2020a
* ncurses/6.2-GCCcore-9.3.0
* bzip2/1.0.8-GCCcore-9.3.0
* cURL/7.69.1-GCCcore-9.3.0
* CMake/3.16.4-GCCcore-9.3.0
* python/anaconda3

## Compiling the code

This hydrocode may be compiled from the root directory using the Makefile. This
is done with the command `make all`. The end product is the hydrocode
executable: "./bin/Hydro1D".

## Running the code

The program may be run fully by running the "./run_Hydro1D" bash script. This
script does the following:

* Generate and interpolate initial conditions by solving the Lane-Emden
equation based on parameters in "./config/params".

* Run the hydrocode for the specified number of iterations.

* Process and plot the output of the hydrocode (with "./plot.py"). Plots are
saved in the "./doc/figs/" directory.

## Elements

* `./config/` : Contains parameter information.

* `./bin/` : Created upon compiling manually or with `make`. Contains
             binaries/executables (the programs).

* `./doc/` : Contains results and the description of the assignment.

* `./fort/` : Testing with the Lane-Emden solver and interpolation.

* `./output/` : Created upon compiling with `make` or `make all`. Contains
                the data files generated by the programs.

* `./src/` : The source code.
