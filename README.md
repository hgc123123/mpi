# mpi

```
module load openmpi
mpic++ hello.c -o hello
mpirun -np 2 ./hello
```

mpi+openmp
```
module load openmpi
mpicc -fopenmp hybrid.c -o hybrid
```

使用intel编译的命令
```
module load intel-oneapi-compilers/2021.4.0
module load intel-oneapi-mpi/2021.4.0

mpicxx hello_mpi.c -o hello_mpi
mpirun -np 2 ./hello_mpi
```
