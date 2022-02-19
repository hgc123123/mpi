int MPI_Allgather(const void *sendbuf, int  sendcount,
     MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm)
int MPI_Iallgather(const void *sendbuf, int  sendcount,
     MPI_Datatype sendtype, void *recvbuf, int recvcount,
     MPI_Datatype recvtype, MPI_Comm comm, MPI_Request *request)


#include<mpi.h>
#include<iostream>
using namespace std;
#define N 3
int main(int argc,char **argv){
    int i,myrank,nprocs;
    int *send_buffer;
    int *recv_buffer;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    send_buffer=new int[N];
    for (i = 0; i < N; i++) {
        send_buffer[i]=myrank*10+i;
    }
    recv_buffer=new int[N*nprocs];
    MPI_Allgather(send_buffer,N,MPI_INT,recv_buffer,N,MPI_INT,MPI_COMM_WORLD);

    for (i = 0; i < N*nprocs; ++i) {
        cout<<"myrank = "<<myrank<<", recv_buffer["<<i<<"]= "<<recv_buffer[i]<<endl;
    }
    delete []send_buffer;
    delete []recv_bufffer;
    MPI_Finalize();
    return 0;
}


[hpc@cas006 C_test]$ mpic++  MPI_Allgather.c -o MPI_Allgather
[hpc@cas006 C_test]$ mpirun --oversubscribe -np 4 ./MPI_Allgather
myrank = 3, recv_buffer[0]= 0
myrank = 3, recv_buffer[1]= 1
myrank = 3, recv_buffer[2]= 2
myrank = 3, recv_buffer[3]= 10
myrank = 3, recv_buffer[4]= 11
myrank = 3, recv_buffer[5]= 12
myrank = 3, recv_buffer[6]= 20
myrank = 3, recv_buffer[7]= 21
myrank = 3, recv_buffer[8]= 22
myrank = 3, recv_buffer[9]= 30
myrank = 3, recv_buffer[10]= 31
myrank = 3, recv_buffer[11]= 32

myrank = 1, recv_buffer[0]= 0
myrank = 1, recv_buffer[1]= 1
myrank = 1, recv_buffer[2]= 2
myrank = 1, recv_buffer[3]= 10
myrank = 1, recv_buffer[4]= 11
myrank = 1, recv_buffer[5]= 12
myrank = 1, recv_buffer[6]= 20
myrank = 1, recv_buffer[7]= 21
myrank = 1, recv_buffer[8]= 22
myrank = 1, recv_buffer[9]= 30
myrank = 1, recv_buffer[10]= 31
myrank = 1, recv_buffer[11]= 32

myrank = 2, recv_buffer[0]= 0
myrank = 2, recv_buffer[1]= 1
myrank = 2, recv_buffer[2]= 2
myrank = 2, recv_buffer[3]= 10
myrank = 2, recv_buffer[4]= 11
myrank = 2, recv_buffer[5]= 12
myrank = 2, recv_buffer[6]= 20
myrank = 2, recv_buffer[7]= 21
myrank = 2, recv_buffer[8]= 22
myrank = 2, recv_buffer[9]= 30
myrank = 2, recv_buffer[10]= 31
myrank = 2, recv_buffer[11]= 32

myrank = 0, recv_buffer[0]= 0
myrank = 0, recv_buffer[1]= 1
myrank = 0, recv_buffer[2]= 2
myrank = 0, recv_buffer[3]= 10
myrank = 0, recv_buffer[4]= 11
myrank = 0, recv_buffer[5]= 12
myrank = 0, recv_buffer[6]= 20
myrank = 0, recv_buffer[7]= 21
myrank = 0, recv_buffer[8]= 22
myrank = 0, recv_buffer[9]= 30
myrank = 0, recv_buffer[10]= 31
myrank = 0, recv_buffer[11]= 32
