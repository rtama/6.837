Build Instructions (Athena with Makefile)
==================
$ mkdir build
$ cd build
$ cmake ..
$ make

Parameters:
  e: euler  
  t: trapezoidal - timestep < 0.001 will render cloth and chain
  r: RK4 - timestep < 0.01 will render cloth and chain

"A" keypress will render new particles into the system

Collaboration: None

