#!/bin/bash -l
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive
#SBATCH --cpu-freq=2200000
#SBATCH -t 04:00:00
#SBATCH --constraint=hwperf

# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel
module load likwid/5.3.0

# TODO allocate a compute node
#salloc -N 1 --ntasks-per-node=1 --exclusive --cpu-freq=2200000 -t 02:00:00

# This line creates / overrides a result csv file
#echo > result.csv

# TODO run benchmark 1
# execute measurement with for loop
# 32 measurement points, exponentially distributed: 1 KiB - 128 MiB, each with 1000 ms as minimal runtime
# results should be appended to the result.csv (see >> operator)
# input parameter:
# to run an executable:
# 	srun ../bin/vecSum [size of the vector in KiB]
for ((i = 0; i < 32; i++)); do
    srun likwid-perfctr -o result_i=$i.csv -O --stats -C 0 -c 0 -f -m -g MEM_UOPS_RETIRED_LOADS_ALL:PMC1,MEM_LOAD_UOPS_RETIRED_L1_HIT:PMC2 ../bin/jacobi $(bc <<< "scale=0; sqrt((($(bc <<< "1.462449973 ^ $i")*1024)/(2*8)))") $(bc <<< "scale=0; sqrt((($(bc <<< "1.462449973 ^ $i")*1024)/(2*8)))")
done

for ((i = 0; i < 32; i++)); do
    srun likwid-perfctr -o result_2_i=$i.csv -O --stats -C 0 -c 0 -f -m -g MEM_UOPS_RETIRED_LOADS_ALL:PMC1,MEM_LOAD_UOPS_RETIRED_L1_HIT:PMC2 ../bin/jacobi_2 $(bc <<< "scale=0; sqrt((($(bc <<< "1.462449973 ^ $i")*1024)/(2*8)))") $(bc <<< "scale=0; sqrt((($(bc <<< "1.462449973 ^ $i")*1024)/(2*8)))")
done

# Note: copy the result.csv to a local machine!
touch ready
