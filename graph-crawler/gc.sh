#!/bin/sh
#SBATCH --job-name=graph_crawler
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G
make

#example tests
./gc Michael Schumacher 2 > michael_schumacher_2.txt
./gc Tom Hanks 3 > tom_hanks_3.txt
./gc Emma Watson 1 > emma_watson_1.txt

echo "Test runs completed."