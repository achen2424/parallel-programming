#!/bin/bash
#SBATCH --job-name=nbody-comparison
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G
#SBATCH --output=output.txt
#SBATCH --error=timing.txt

make all

echo "---Test Case 1: 5 bodies, dt=300s, 5,000,000 steps, print every 10,000---" >> timing.txt
echo "Parallel version:" >> timing.txt
./nbody-par 5 300 5000000 10000 > sim-par-1.out 2>> timing.txt
echo "Sequential version:" >> timing.txt
./nbody-seq 5 300 5000000 10000 > sim-seq-1.out 2>> timing.txt
echo "" >> timing.txt

echo "---Test Case 2: 100 bodies, dt=300s, 50,000 steps, print every 500---" >> timing.txt
echo "Parallel version:" >> timing.txt
./nbody-par 100 3000 50000 500 > sim-par-2.out 2>> timing.txt
echo "Sequential version:" >> timing.txt
./nbody-seq 100 3000 50000 500 > sim-seq-2.out 2>> timing.txt
echo "" >> timing.txt

echo "---Test Case 3: Solar system, dt=200s, 5,000,000 steps, print every 10,000---" >> timing.txt
echo "Parallel version:" >> timing.txt
./nbody-par planet 200 5000000 10000 > sim-par-3.out 2>> timing.txt
echo "Sequential version:" >> timing.txt
./nbody-seq planet 200 5000000 10000 > sim-seq-3.out 2>> timing.txt