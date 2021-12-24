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
    static const double msol = 1.989e33;                 // Solar mass (g)

    // Newton gravitation constant
    static const double G = 6.6743e-8;                   // Dyne cm g

    // Nuclear density
    static const double rhoNuc = 2.3e14;                 // g cm^-3

    // Central density (at t = 0)
    static const double rhoC = 1.0e7;                    // g cm^-3

    // Polytropic (gamma = 4/3) pressure constant for 10 m_sol
    // static const double K4_3 = 1.2e15;                // cgs
    static const double K4_3 = 1.78373175076e15;         // cgs

    // Polytropic (gamma = 2) pressure constant
    //    Based on Baron, Cooperstein, Kahana 1985 with x = 0.33, gamma = 3
    //    P = [ K0 / (9 * gamma * rhoNuc^2 * m_n) ] * rho^3
    const double m_n = 1.674920e-24;                     // Mass of neutron (g)
    const double K0 = 140.0 * 1.60218e-6;                // erg
    const double gamma = 3.0;

    static const double K3 = K0 / (9.0 * gamma * pow(rhoNuc, 2.0) * m_n);
}