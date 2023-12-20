#!/bin/bash -l
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive
#SBATCH --cpu-freq=2200000
#SBATCH -t 02:00:00
#SBATCH --tasks-per-node=20

# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel
module load likwid

# TODO allocate a compute node
#salloc -N 1 --ntasks-per-node=1 --exclusive --cpu-freq=2200000 -t 02:00:00 --tasks-per-node=20

# This line creates / overrides a result csv file
echo "Threads,MegaUpdatesPerSecond,ActualRuntime" > result.csv

# TODO run benchmark 1
# execute measurement with for loop
# 32 measurement points, exponentially distributed: 4 GiB, each with 1000 ms as minimal runtime
# results should be appended to the result.csv (see >> operator)
# input parameter:
# to run an executable:
# 	srun ../bin/vecSum [size of the vector in KiB]
for ((i = 1; i <= 20; i++)); do
    make -C .. clean
    make -C .. THREADS="-DTHREADS=$i"
    srun ../bin/jacobi $(bc <<< "scale=0; sqrt(((4*1024*1024*1024)/(2*8)))") $(bc <<< "scale=0; sqrt(((4*1024*1024*1024)/(2*8)))") >> result.csv
done

# This line creates / overrides a result csv file
echo "Threads,MegaUpdatesPerSecond,ActualRuntime" > result_pinned.csv

for ((i = 1; i <= 10; i++)); do
    make -C .. clean
    make -C .. THREADS="-DTHREADS=$i"
    srun likwid-pin -c E:S0:$i:1:1 ../bin/jacobi $(bc <<< "scale=0; sqrt(((4*1024*1024*1024)/(2*8)))") $(bc <<< "scale=0; sqrt(((4*1024*1024*1024)/(2*8)))") >> result_pinned.csv
done

for ((i = 1; i <= 10; i++)); do
    make -C .. clean
    make -C .. THREADS="-DTHREADS=$(($i+10))"
    srun likwid-pin -c E:S0:10:1:1@S1:$i:1:1 ../bin/jacobi $(bc <<< "scale=0; sqrt(((4*1024*1024*1024)/(2*8)))") $(bc <<< "scale=0; sqrt(((4*1024*1024*1024)/(2*8)))") >> result_pinned.csv
done

# Note: copy the result.csv to a local machine!
touch ready
