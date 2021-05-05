program hydro
        use, intrinsic :: iso_fortran_env
        implicit none

        real zero = 1d-70
        real pi4 = 4.0 * 3.141592
        real pi4_sq = pi4 * pi4
        real one_third = 1.0 / 3.0
        real four_thirds = 4.0 / 3.0
        real pi4_3 = pi4 * one_third
        real G = 6.6743d-8
        real K4_3 = zero
        real K3 = zero
        real rhoc = 10.0 * 1.989 * 1000.0 / (pi4 * (one_third - 0.25))
        real rhoNuc = 2.3d14

        
end program hydro
