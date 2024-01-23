#!/bin/bash -l

sbatch.tinygpu ./tinygpu.sh

while [ ! -f ready ]; do
	sleep 60
done
rm ready
