#!/bin/sh
#SBATCH --job-name=level_client
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G
make

mkdir -p output

#example tests
./level_client "Michael Schumacher" 2 > output/michael_schumacher_2.txt
./level_client "Tom Hanks" 1 > output/tom_hanks_1.txt
./level_client "Viola Davis" 2 > output/viola_davis_2.txt

echo "Test runs completed."