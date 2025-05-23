#!/bin/bash
#SBATCH --job-name=nbody-cuda
#SBATCH --partition=GPU
#SBATCH --time=01:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --gres=gpu:TitanV:1

module load cuda/12.4
> output.txt

OUTPUT="output.txt"

echo "GPU TESTS" >> $OUTPUT

echo "Test Case 0: planet dt=200 steps=5000 print_every=100 block_size=128" >> $OUTPUT
./nbody_gpu planet 200 5000 100 128 >> $OUTPUT
echo "" >> $OUTPUT

echo "Test Case 1: particles=1000 dt=1 steps=1000 print_every=50 block_size=256" >> $OUTPUT
./nbody_gpu 1000 1 1000 50 256 >> $OUTPUT
echo "" >> $OUTPUT

echo "Test Case 2: particles=10000 dt=0.1 steps=500 print_every=100 block_size=256" >> $OUTPUT
./nbody_gpu 10000 0.1 500 100 256 >> $OUTPUT
echo "" >> $OUTPUT

echo "Test Case 3: particles=100000 dt=0.1 steps=500 print_every=100 block_size=512" >> $OUTPUT
./nbody_gpu 100000 0.1 500 100 512 >> $OUTPUT
echo "" >> $OUTPUT

echo "CPU TESTS" >> $OUTPUT

echo "Test Case 1: particles=1000 dt=1 steps=1000 print_every=50" >> $OUTPUT
./nbody_cpu 1000 1 1000 50 >> $OUTPUT
echo "" >> $OUTPUT

echo "Test Case 2: particles=10000 dt=0.1 steps=500 print_every=100" >> $OUTPUT
./nbody_cpu 10000 0.1 500 100 >> $OUTPUT
echo "" >> $OUTPUT

echo "Test Case 3: particles=20000 dt=0.1 steps=10 print_every=1" >> $OUTPUT
./nbody_cpu 20000 0.1 10 1 >> $OUTPUT
echo "" >> $OUTPUT

echo "Results are saved to $OUTPUT"