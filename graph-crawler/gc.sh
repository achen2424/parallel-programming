#!/bin/sh
#SBATCH --job-name=graph_crawler
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G
make

mkdir -p output

#example tests
./gc "Michael Schumacher" 2 > output/michael_schumacher_2.txt
./gc "Tom Hanks" 3 > output/tom_hanks_2.txt
./gc "Viola Davis" 1 > output/viola_davis_1.txt

echo "Test runs completed."