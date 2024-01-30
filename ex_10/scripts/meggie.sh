#!/bin/bash -l
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive
#SBATCH --cpu-freq=2200000
#SBATCH -t 02:00:00

# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel
module load mkl

# TODO allocate a compute node
#salloc

# This line creates / overrides a result csv file
#touch

# TODO run benchmark 1
# execute measurement with for loop
# 32 measurement points, exponentially distributed: 4 GiB, each with 1000 ms as minimal runtime
# results should be appended to the result.csv (see >> operator)
# input parameter:
# to run an executable:
# 	srun ../bin/vecSum [size of the vector in KiB]
make -C .. clean
make -C .. dgemm_cpu
srun ../bin/dgemm_cpu $(bc <<< "scale=0; sqrt(((15*1024*1024*1024)/(2*8)))") > dgemm_cpu.txt

# Note: copy the result.csv to a local machine!
touch ready
