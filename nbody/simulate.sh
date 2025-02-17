#!/bin/sh
#SBATCH --job-name=mergesort
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G

output_file="simulation_times.tsv"

echo "5000000 steps, 200 dt, 9 particles" >> $output_file
# 8 planets and the sun
./nbody 5000000 200 9 >> $output_file

echo "10000 steps, 1 dt, 100 particles" >> $output_file
./nbody 10000 1 100 >> $output_file

echo "10000 steps, 1 dt, 1000 particles" >> $output_file
./nbody 10000 1 1000 >> $output_file
