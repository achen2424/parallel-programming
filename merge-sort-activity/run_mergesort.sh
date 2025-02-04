#!/bin/sh
#SBATCH --job-name=mergesort
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G

echo "Size, Time" 
for size in 10 100 1000 10000 100000 1000000 10000000 100000000 1000000000
do 
    echo "Running for size: $size"
   ./mergesort $size
done
echo "Done!"