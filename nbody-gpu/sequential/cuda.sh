#!/bin/bash
#SBATCH --job-name=yourprogramname
#SBATCH --partition=GPU
#SBATCH --time=00:10:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --gres=gpu:1

module load cuda/12.4
> output.txt

OUTPUT="output.txt"

echo "TEST CASE 1: input_config=planet dt=200 steps=5000 print_every=100 block_size=128" >> $OUTPUT
./nbody_gpu planet 200 5000 100 128 >> $OUTPUT
echo "" >> $OUTPUT

echo "TEST CASE 2: num_particles=1000 dt=1 steps=1000 print_every=50 block_size=256" >> $OUTPUT
./nbody_gpu 1000 1 1000 50 256 >> $OUTPUT
echo "" >> $OUTPUT

echo "TEST CASE 3: num_particles=10000 dt=0.1 steps=500 print_every=100 block_size=256" >> $OUTPUT
./nbody_gpu 100000 0.1 500 100 256 >> $OUTPUT

echo "TEST CASE 4: num_particles=100000 dt=0.1 steps=500 print_every=100 block_size=512" >> $OUTPUT
./nbody_gpu 100000 0.1 500 100 512 >> $OUTPUT

echo "Results are saved to $OUTPUT"