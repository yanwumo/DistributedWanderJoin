Distributed Wander Join
====================================

## Prerequisites

* CMake

* OpenMPI (Other MPI versions may have different CMake flags, but they should work)

## Build
To build:

    cmake .
    make

## Run

TPC-H data are assumed to be placed under ../data/*.tbl.

To run:

    mpiexec -host hostname1,hostname2,hostname3,hostname4 -np 4 ./DistributedWanderJoin
