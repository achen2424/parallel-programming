#!/bin/bash
#SBATCH --job-name=nbody-comparison
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G
#SBATCH --output=output.txt
#SBATCH --error=timing.txt

make all

echo "---Test Case 1: 10 bodies, 1 step, 10,000 timesteps---" >> timing.txt
echo "Parallel version:" >> timing.txt
./nbody-par 10 1 10000 100 > sim-par-1.out 2>> timing.txt
echo "Sequential version:" >> timing.txt
./nbody-seq 10 1 10000 100 > sim-seq-1.out 2>> timing.txt
echo "" >> timing.txt

echo "---Test Case 2: 50 bodies, 1 step, 5,000 timesteps---" >> timing.txt
echo "Parallel version:" >> timing.txt
./nbody-par 50 1 5000 50 > sim-par-2.out 2>> timing.txt
echo "Sequential version:" >> timing.txt
./nbody-seq 50 1 5000 50 > sim-seq-2.out 2>> timing.txt
echo "" >> timing.txt

echo "---Test Case 3: 100 bodies, 1 step, 2,000 timesteps---" >> timing.txt
echo "Parallel version:" >> timing.txt
./nbody-par 100 1 2000 20 > sim-par-3.out 2>> timing.txt
echo "Sequential version:" >> timing.txt
./nbody-seq 100 1 2000 20 > sim-seq-3.out 2>> timing.txt