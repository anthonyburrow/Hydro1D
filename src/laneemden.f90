program laneem
! code taken from http://www.astro.utu.fi/~cflynn/Stars/l4.html
        use, intrinsic :: iso_fortran_env
        implicit none

        real x, dxdt, n, dt, xlast, dxdtlast, t
        integer i
        character*50 name

        
        ! write(6,*) 'Enter n, the polytrope index '
        ! read(5,*) n
        
        n = 3

        if (n.ge.5) then
          write(6,*) 'n is too big, star radius is infinite'
          stop
        end if

        ! write(6,*) 'Enter name of results file'
        ! read(5,*) name

        name = './output/poly3'

        open(20,file=name,status='new')


        x    = 1.0   
        dxdt = 0.0
        t    = 0.0001


        dt = 0.001


        do 100 i = 1, 10000

          dxdt = dxdt - ( 2.0*dxdt/t + x**n )*dt
        
          x = x + dxdt*dt 

          t = t + dt
        

          write(20,*) t,x,dxdt

          if (x.lt.0.0) goto 999

100     continue

999     continue

        end
