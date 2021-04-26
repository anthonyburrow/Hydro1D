#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

namespace myHydro
{
    // Math constants
    static const double zero = 1e-70;
    static const double pi4 = 4.0 * M_PI;
    static const double pi4_sq = pi4 * pi4;
    static const double one_third = 1.0 / 3.0;
    static const double four_thirds = 4.0 / 3.0;
    static const double pi4_3 = pi4 * one_third;

    // Newton gravitation constant
    static const double G = 6.6743e-8;   // cm^3 g^-1 s^-2

    // Polytropic (gamma = 4/3) pressure constant
    static const double K4_3 = zero;   //change

    // Polytropic (gamma = 3) pressure constant
    static const double K3 = zero;   //change

    // Central density (linear, M = 10 Msol, R = 10^10 cm)
    static const double rhoc = 10.0 * 1.989 * 1000.0 / (pi4 * (one_third - 0.25));

    // Nuclear density
    static const double rhoNuc = 2.3e14;

    // Radiation constant
    // static const double a = 7.5657e-15;   // erg cm^-3 K^-4

    // Speed of light
    // static const double c = 2.99792458e10;   // cm s^-1
}