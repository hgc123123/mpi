int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm)
int MPI_Iscatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    void *recvbuf, int recvcount, MPI_Datatype recvtype, int root,
    MPI_Comm comm, MPI_Request *request)



#include<iostream>
#include<mpi.h>
using namespace std;
int main(int argc,char **argv){
    int myrank,nprocs;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    int sendbuf[4]={34,23,1,5};
    int recv_data;
    MPI_Scatter(&sendbuf,1,MPI_INT,&recv_data,1,MPI_INT,0,MPI_COMM_WORLD);
    cout<<"myrank: "<<myrank<<"recieved data is :"<<recv_data<<endl;
    MPI_Finalize();
    return 0;
}

[hpc@cas006 C_test]$ mpic++ MPI_Scatter.cpp -o MPI_Scatter
[hpc@cas006 C_test]$ mpirun --oversubscribe -np 4 ./MPI_Scatter
myrank: 0recieved data is :34
myrank: 1recieved data is :23
myrank: 2recieved data is :1
myrank: 3recieved data is :5
