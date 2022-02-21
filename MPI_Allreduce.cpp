int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count,
                  MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
int MPI_Iallreduce(const void *sendbuf, void *recvbuf, int count,
                   MPI_Datatype datatype, MPI_Op op, MPI_Comm comm,
                   MPI_Request *request)

#include<iostream>
#include<mpi.h>
#include<assert.h>
#include<time.h>
using namespace std;

float *create_rand_nums(int num_elements){
    float *rand_nums=new float[num_elements];
    int i;
    for (i = 0; i < num_elements; ++i) {
        rand_nums[i]=(rand()/(float)RAND_MAX);
    }
    return rand_nums;
}
int main(int argc,char **argv){
    int num_elements=atoi(argv[1]);
    int nprocs,myrank;
    int i;
    double startTime;
    //startTime=MPI_Wtime();
    //cout<<"startTime: "<<startTime<<endl;
    MPI_Init(NULL,NULL);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    startTime=MPI_Wtime();
    cout<<"startTime: "<<startTime<<endl;
    srand(time(NULL)*myrank);
    float *rand_nums=NULL;
    rand_nums=create_rand_nums(num_elements);

    float localSum=0;
    for (i = 0; i < num_elements; ++i) {
        localSum+=rand_nums[i];
    }
    float globalSum=0;
    MPI_Allreduce(&localSum,&globalSum,1,MPI_FLOAT,MPI_SUM,MPI_COMM_WORLD);
    cout<<endl;
    cout<<"myrank is: "<<myrank<<" globlaSum is: "<<globalSum<<endl;
    delete []rand_nums;
    MPI_Barrier(MPI_COMM_WORLD);
    cout<<"elapsed time is: "<<(MPI_Wtime()-startTime)<<endl;
    MPI_Finalize();
}

[hpc@node040 mpi]$ mpirun --oversubscribe -np 20 MPI_Reduce 90000
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0
startTime: 0

myrank is: 0 globlaSum is: 899566



myrank is: 12 globlaSum is: 899566

myrank is: 16 globlaSum is: 899566
myrank is: 8 globlaSum is: 899566
myrank is: 1 globlaSum is: 899566


myrank is: 3 globlaSum is: 899566

myrank is: 2 globlaSum is: 899566
myrank is: 13 globlaSum is: 899566


myrank is: 17 globlaSum is: 899566
myrank is: 9 globlaSum is: 899566

myrank is: 19 globlaSum is: 899566

myrank is: 5 globlaSum is: 899566

myrank is: 14 globlaSum is: 899566

myrank is: 4 globlaSum is: 899566


myrank is: 6 globlaSum is: 899566

myrank is: 7 globlaSum is: 899566
myrank is: 15 globlaSum is: 899566

myrank is: 10 globlaSum is: 899566

myrank is: 18 globlaSum is: 899566

myrank is: 11 globlaSum is: 899566
elapsed time is: 0.00493721
elapsed time is: 0.00515969
elapsed time is: 0.00510764
elapsed time is: 0.00501933
elapsed time is: 0.00510358
elapsed time is: 0.00500006
elapsed time is: 0.00506233
elapsed time is: 0.00511038
elapsed time is: 0.00517063
elapsed time is: 0.00501531
elapsed time is: 0.0053612
elapsed time is: 0.00539893
elapsed time is: 0.005514
elapsed time is: 0.00531545
elapsed time is: 0.00553847
elapsed time is: 0.00592245
elapsed time is: 0.00578152
elapsed time is: 0.00587675
elapsed time is: 0.0058107
elapsed time is: 0.00596286
