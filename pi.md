
```
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <mpi.h>

using namespace std;

double f(double x){
    return 4.0/(1.0+x*x);
}

int main(int argc,char *argv[])
{
    int myid,numprocs;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    MPI_Status status;
    double startTime=0;
    double endTime=0;
    startTime=MPI_Wtime();

    int n;
    double ans=0;
    if(myid==0){
    	cout << "Please input n: ";
	cin >> n;
    }

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
    double h=1.0/n;
    double x;
    for(int i=myid+1;i<=n;i+=numprocs){
    	x=h*(i-0.5);
	ans+=f(x);
    }

    double mypi=h*ans;
    MPI_Reduce(&mypi,&ans,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(myid==0){
    	cout<<"Pi is: "<<ans<<endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    endTime=MPI_Wtime();
    if(myid==0){
    	cout<<"Tasks over"<<endl;
	cout<<"Cost time: "<<endTime-startTime<<" s. "<<endl;
    }
    MPI_Finalize();
    return 0;

}

[hpchgc@node838 mpi]$ mpirun -np 1 pi
Please input n: 1000000000
Pi is: 3.14159
Tasks over
Cost time: 6.23019 s.
[hpchgc@node838 mpi]$ mpirun -np 2 pi
Please input n: 1000000000
Pi is: 3.14159
Tasks over
Cost time: 3.96875 s.
[hpchgc@node838 mpi]$ mpirun -np 4 pi
Please input n: 1000000000
Pi is: 3.14159
Tasks over
Cost time: 2.44586 s.
```
