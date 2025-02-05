#!/bin/sh
#SBATCH --job-name=mergesort
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G
:'
output_file="mergesort_output.csv"
echo "size,time(microseconds)" > $output_file

for size in 10 100 1000 10000 100000 1000000 10000000 100000000 1000000000
do 
    ./mergesort $size >> $output_file
done
echo "Done!"
'

./mergesort 10
./mergesort 100
./mergesort 1000
./mergesort 10000
./mergesort 100000
./mergesort 1000000
./mergesort 10000000
./mergesort 100000000
./mergesort 1000000000
