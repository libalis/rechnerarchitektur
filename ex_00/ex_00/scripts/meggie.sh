#!/bin/bash -l
#SBATCH <job argument 0> # e.g. –N 1
#SBATCH <job argument 1>
#SBATCH <job argument n>

# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel

# TODO allocate a compute node
salloc -N 1 --ntasks-per-node=1 --exclusive --cpu-freq=2200000 -t 01:00:00;

# This line creates / overrides a result csv file
echo "ArraySize,AdditionsPerSecond,ActualRuntime,MinimalRuntime" > result.csv

# TODO run benchmark 1
# execute measurement with for loop
# 32 measurement points, exponentially distributed: 1 KiB - 128 MiB, each with 1000 ms as minimal runtime
# results should be appended to the result.csv (see >> operator)
# input parameter:
# to run an executable:
# 	srun ../bin/vecSum [size of the vector in KiB]
distribution=1;
for i in {1..20}; do
    for (( j=1; j<=32; j++ )); do
        srun ../bin/main $(( distribution << $j )) 1000 >> result.csv
    done
done

# Note: copy the result.csv to a local machine!
scp result.csv cu14mowo@cipterm0.cip.cs.fau.de:.

touch ready
