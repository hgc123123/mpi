#include <iostream>
#include <omp.h>
#include <mpi.h>
using namespace std;
static omp_lock_t lock;
int main(int argc,char **argv) {

    int nprocs, myrank, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int np=0,iam=0;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Get_processor_name(processor_name, &namelen);
    omp_init_lock(&lock);
    #pragma omp parallel default(shared) private(iam, np)
    {
	omp_set_lock(&lock);
        np=omp_get_num_threads();
        iam=omp_get_thread_num();
        cout<<"hello from thread "<<iam<<" out of "<<np<<" from processor "<<myrank<<" out of "<<nprocs<<" on "<<processor_name<<endl;
	cout<<endl;
	omp_unset_lock(&lock);
    }
    MPI_Finalize();
}

[hpc@node040 mpi]$ mpic++ -fopenmp MPI_OpenMP.cpp -o MPI_OpenMP
[hpc@node040 mpi]$ export OMP_NUM_THREADS=2
[hpc@node040 mpi]$ mpirun --oversubscribe  -np 2 MPI_OpenMP


[hpc@node040 mpi]$ mpirun --oversubscribe  -np 2 MPI_OpenMP
hello from thread 0 out of 2 from processor 1 out of 2 on node040.pi.sjtu.edu.cn

hello from thread 1 out of 2 from processor 1 out of 2 on node040.pi.sjtu.edu.cn

hello from thread 0 out of 2 from processor 0 out of 2 on node040.pi.sjtu.edu.cn

hello from thread 1 out of 2 from processor 0 out of 2 on node040.pi.sjtu.edu.cn
