parallel programming hw4 gameoflife.c
=======================================
Kyle Wong
13.4.21
jhed: kwong23

Implementation of the game of life in c

How to build:
use the makefile by typing: make
or you can type: mpicc gameoflife.c -o gameoflife

How to run:
type: mpirun -np num ./gameoflife
where num is the number of processors to run (1, 2, 4, 8, or 16)

This implementation used OpenMPI.
Specifically it used MPI synchronous send and MPI receive to
communicate grid updates between processors.
(MPI_Ssend and MPI_Recv)

The code is set to output the grid at each iteration, 
and the code is set to run for 64 iterations.

