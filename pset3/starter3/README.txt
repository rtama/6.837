Build Instructions (Athena with Makefile)
==================
$ mkdir build
$ cd build
$ cmake ..
$ make

Parameters:
  trapezoidal - timestep < 0.001 will render cloth and chain
  RK4 - timestep < 0.01 will render cloth and chain

Can alter particles in cloth and chain in constants in clothsystem.cpp and pendulumsystem.cpp.


Collaboration: None

References: only online cplusplus.com, lecture notes, and piazza. 

Problems: Not that I'm aware of.

Extra Credit: 
    - 'P' toggles between holding 2 corners of cloth and the middle
    - 'W' toggles a gentle breeze on and off

Comments: I really enjoyed it! 
