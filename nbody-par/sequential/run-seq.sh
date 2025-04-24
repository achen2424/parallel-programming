#!/bin/bash
#SBATCH --job-name=nbody-seq
#SBATCH --partition=Centaurus
#SBATCH --output=nbody-seq.log
#SBATCH --time=00:10:00
#SBATCH --mem=2G
#SBATCH --cpus-per-task=1

module load gcc

make nbody-seq
make solar-seq.out
make solar-seq.pdf