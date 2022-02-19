int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm)
int MPI_Igather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm, MPI_Request *request)



#include<mpi.h>
#include<iostream>
using namespace std;
int main(int argc,char **argv){
    int myrank;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    const void *partial;
    void *total;
    if(myrank==0){
        partial="000,";
    }else if(myrank==1){
        partial="111,";
    }else if(myrank==2){
        partial="222,";
    }
    MPI_Gather(partial,4,MPI_CHAR,total,4,MPI_CHAR,0,MPI_COMM_WORLD);
    if(myrank==0){
        cout<<(char *)total<<endl;
    }
    MPI_Finalize();
}

[hpc@cas006 C_test]$ mpic++ MPI_gather.cpp -o MPI_gather
[hpc@cas006 C_test]$ mpirun --oversubscribe  -np 3 ./MPI_gather
000,111,222,
