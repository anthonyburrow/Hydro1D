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

    // Units
    static const double msol = 1.989e33;   // Solar mass (g)

    // Newton gravitation constant
    static const double G = 6.6743e-8;   // cm^3 g^-1 s^-2

    // Nuclear density
    static const double rhoNuc = 2.3e14;   // g cm^-3

    // Polytropic (gamma = 4/3) pressure constant
    static const double K4_3 = 3.8468e14;   // cgs

    // Polytropic (gamma = 2) pressure constant
    //    Based on Baron, Cooperstein, Kahana 1985 with x = 0.33, gamma = 2
    //    P = [ K0 / (9 * gamma * rhoNuc * m_n) ] * rho^2
    const double m_n = 1.674920e-24;   // Mass of neutron (g)
    const double K0 = 220.0 * 1.60218e-6;   // erg

    static const double K2 = K0 / (18.0 * rhoNuc * m_n);

    // Central density (M = 10 Msol, R = 10^10 cm)
    static const double rhoc = 10.0 * myHydro::msol / (pi4 * pow(1e10, 3) * (one_third - 0.25));
    // static const double rhoc = 2e10;   // g cm^-3
}