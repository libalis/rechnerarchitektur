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

# TODO allocate a compute node
salloc -N 1 --ntasks-per-node=1 --exclusive --cpu-freq=2200000 -t 02:00:00

# This line creates / overrides a result csv file
echo "ArraySize,AdditionsPerSecond,ActualRuntime,MinimalRuntime" > result.csv

# TODO run benchmark 1
# execute measurement with for loop
# 32 measurement points, exponentially distributed: 1 KiB - 128 MiB, each with 1000 ms as minimal runtime
# results should be appended to the result.csv (see >> operator)
# input parameter:
# to run an executable:
# 	srun ../bin/vecSum [size of the vector in KiB]
for ((i = 0; i < 32; i++)); do
    for j in {1..20}; do
        srun ../bin/vecSum $(bc <<< "1.462449973 ^ $i") 1000 >> result.csv
    done
done

echo >> result.csv

for ((i = 0; i < 32; i++)); do
    for j in {1..20}; do
        srun ../bin/vecSum $((32*1024)) $(bc <<< "1.345962495 ^ $i") >> result.csv
    done
done

# Note: copy the result.csv to a local machine!
touch ready
