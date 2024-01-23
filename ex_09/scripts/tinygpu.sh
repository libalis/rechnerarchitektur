#!/bin/bash -l
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH --cpu-freq=2900000
#SBATCH --time 02:00:00
#SBATCH --cpus-per-task=8
#SBATCH --gres=gpu:rtx3080:1
#SBATCH --export=NONE

# Do not export environment variables
unset SLURM_EXPORT_ENV

# Set number of threads to requested cpus-per-task
OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel
module load likwid/5.3.0
module load cuda

# Allocate a compute node
#salloc

# This line creates / overrides a result csv file
#touch

# Run benchmark
# execute measurement with for loop
# 32 measurement points, exponentially distributed: 4 GiB, each with 1000 ms as minimal runtime
# results should be appended to the result.csv (see >> operator)
# input parameter:
# to run an executable:
# 	srun ../bin/vecSum [size of the vector in KiB]
make -C .. clean
make -C ..
srun ../bin/jacobi > result_without_copy_overhead.txt

make -C .. clean
make -C .. COPY_TIME="-DCOPY_TIME=1"
srun ../bin/jacobi > result_with_copy_overhead.txt

# Note: copy the result.csv to a local machine!
touch ready
