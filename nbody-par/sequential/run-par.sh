#!/bin/bash
#SBATCH --job-name=nbody-par
#SBATCH --output=nbody-par.log
#SBATCH --time=00:10:00
#SBATCH --mem=2G
#SBATCH --cpus-per-task=4

module load gcc

make nbody-par  
make solar-par.out
make solar-par.pdf