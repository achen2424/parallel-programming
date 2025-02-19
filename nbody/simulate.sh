#!/bin/sh
#SBATCH --job-name=nbody
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G

output_file="simulation_times.csv"

echo "9 particles (sun and 8 planets), 200 dt, 5000000 steps, 1000 log interval" >> $output_file
./nbody 9 200 5000000 10000 >> $output_file

echo "100 particles, 1 dt, 10000 steps, 100 log interval" >> $output_file
./nbody 100 1 10000 100 >> $output_file

echo "1000 particles, 1 dt, 10000 steps, 500 log interval" >> $output_file
./nbody 1000 1 10000 500 >> $output_file