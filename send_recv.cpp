int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest,
    int tag, MPI_Comm comm)
int MPI_Recv(void *buf, int count, MPI_Datatype datatype,
    int source, int tag, MPI_Comm comm, MPI_Status *status)


#include<mpi.h>
#include<iostream>
int main(int argc,char **argv){
    int rank,buf;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==0) {
        int buf = 12345;
        MPI_Send(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }else if(rank==1){
        MPI_Recv(&buf,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        cout<<buf<<endl;
    }
    MPI_Finalize();
    return 0;
}

[hpc@cas006 C_test]$ mpic++ send_recv.c -o send_recv
[hpc@cas006 C_test]$ mpirun --oversubscribe  -np 2 ./send_recv
12345
