all: nbody

nbody: nbody.cpp
	g++ -O2 nbody.cpp -o nbody

run_local:
	./nbody 100 100 10000 1000

clean:
	rm -f nbody solar.tsv solar.pdf simulation_times.txt

simulate:
	sbatch simulate.sh

view:
	cat simulation_times.txt

plot:
	python3 plot.py solar.tsv solar.pdf
