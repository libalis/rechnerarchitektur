#!/bin/bash -l
#SBATCH -N 1
#SBATCH --ntasks-per-node=1
#SBATCH --exclusive
#SBATCH --cpu-freq=2200000
#SBATCH -t 04:00:00

# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel

# TODO allocate a compute node
#salloc -N 1 --ntasks-per-node=1 --exclusive --cpu-freq=2200000 -t 02:00:00

for x in 768; do
for y in 50; do

make -C .. clean
make -C .. BX="-DBX=$x" BY="-DBY=$y"

# This line creates / overrides a result csv file
echo "EdgeSize,MegaUpdatesPerSecond,ActualRuntime" > result_bx=${x}_by=$y.csv

# TODO run benchmark 1
# execute measurement with for loop
# 32 measurement points, exponentially distributed: 1 MiB - 16 GiB, each with 1000 ms as minimal runtime
# results should be appended to the result.csv (see >> operator)
# input parameter:
# to run an executable:
# 	srun ../bin/vecSum [size of the vector in KiB]
for ((i = 0; i < 32; i++)); do
    srun ../bin/jacobi $(bc <<< "scale=0; sqrt((($(bc <<< "1.367571008 ^ $i")*1024*1024)/(2*8)))") $(bc <<< "scale=0; sqrt((($(bc <<< "1.367571008 ^ $i")*1024*1024)/(2*8)))") >> result_bx=${x}_by=$y.csv
done

done
done

# Note: copy the result.csv to a local machine!
touch ready
