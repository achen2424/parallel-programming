#!/bin/bash
#SBATCH --job-name=nbody-comparison
#SBATCH --partition=Centaurus
#SBATCH --time=00:30:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --mem=4G
#SBATCH --output=result.txt

#test case 1: 10 bodies, 1 step, 10,000 timesteps
echo "Running parallel version for 10 bodies, 1 step, 10,000 timesteps"
./nbody-par 10 1 10000 100
echo "Running sequential version for 10 bodies, 1 step, 10,000 timesteps"
./nbody-seq 10 1 10000 100

#test case 2: 50 bodies, 1 step, 5000 timesteps
echo "Running parallel version for 50 bodies, 1 step, 5000 timesteps"
./nbody-par 50 1 5000 50
echo "Running sequential version for 50 bodies, 1 step, 5000 timesteps"
./nbody-seq 50 1 5000 50

#test case 3: 100 bodies, 1 step, 2000 timesteps
echo "Running parallel version for 100 bodies, 1 step, 2000 timesteps"
./nbody-par 100 1 2000 20
echo "Running sequential version for 100 bodies, 1 step, 2000 timesteps"
./nbody-seq 100 1 2000 20