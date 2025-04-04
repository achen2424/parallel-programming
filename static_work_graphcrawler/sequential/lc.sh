#!/bin/sh
#SBATCH --job-name=level_client
#SBATCH --partition=Centaurus
#SBATCH --time=01:00:00
#SBATCH --mem=32G
make

mkdir -p output

#example tests
./par_level_client "Michael Schumacher" 3 > output/PAR_michael_schumacher_3.txt
./level_client "Michael Schumacher" 3 > output/SEQ_michael_schumacher_3.txt
./par_level_client "Tom Hanks" 1 > output/PAR_tom_hanks_1.txt
./level_client "Tom Hanks" 1 > output/SEQ_tom_hanks_1.txt
./par_level_client "Viola Davis" 2 > output/PAR_viola_davis_2.txt
./level_client "Viola Davis" 2 > output/SEQ_viola_davis_2.txt

echo "Test runs completed."