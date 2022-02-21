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
    MPI_Init(NULL,NULL);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    // Create a random array of elements on all processes.
    srand(time(NULL)*myrank); // Seed the random number generator of processes uniquely
    float *rand_nums=NULL;
    rand_nums=create_rand_nums(num_elements);

    float localSum=0;
    for (i = 0; i < num_elements; ++i) {
        cout<<rand_nums[i]<<" ";
        localSum+=rand_nums[i];
    }
    cout<<endl;
    float globalSum=0;
    MPI_Reduce(&localSum,&globalSum,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
    if(myrank==0){
        cout<<"global sum is: "<<globalSum<<endl;
    }
    cout<<endl;
    delete []rand_nums;
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}
