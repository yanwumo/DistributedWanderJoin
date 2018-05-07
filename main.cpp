#include <iostream>
#include "Q3.h"
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    Q3(static_cast<size_t>(rank), static_cast<size_t>(size)).execute();

    MPI_Finalize();
    return 0;
}