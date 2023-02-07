#include <mpi.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[]) {
    // set up MPI
    MPI_Init(&argc, &argv);

    // get communicator size and my rank
    MPI_Comm comm = MPI_COMM_WORLD;
    int p, rank;
    MPI_Comm_size(comm, &p);
    MPI_Comm_rank(comm, &rank);
    /* code */
    int n = atoi(argv[1]);
    double t1, t2;
    double global_sum;

    t1 = MPI_Wtime();

    //Local computation of sums
    double h = 1.0 / n;
    double local_sum = 0;
    for (int i = rank + 1; i <= n; i += p) {
        local_sum += 4/(1 + (h * h * (i - 0.5) * (i - 0.5)));
    }
    local_sum /= n;

    //add together local sums
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);

    t2 = MPI_Wtime();

    if (rank == 0) {
        printf("Global sum: %.12f\n", global_sum);
        printf("Time elapsed: %f\n", t2 - t1);
    }
    // finalize MPI
    MPI_Finalize();
    return 0;
}
