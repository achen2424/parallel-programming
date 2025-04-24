CXX = g++-14
CXXFLAGS = -O3 -std=c++11
LDFLAGS = -fopenmp

nbody-seq: nbody-seq.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

nbody-par: nbody-par.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@

all: nbody-seq nbody-par

#solar system outputs
solar-seq.out: nbody-seq
	date
	./nbody-seq planet 200 5000000 10000 > solar-seq.out
	date

solar-par.out: nbody-par
	date
	OMP_NUM_THREADS=4 ./nbody-par planet 200 5000000 10000 > solar-par.out
	date

#pdf generation
solar-seq.pdf: solar-seq.out
	python3 plot.py solar-seq.out solar-seq.pdf 1000

solar-par.pdf: solar-par.out
	python3 plot.py solar-par.out solar-par.pdf 1000

#random particle ouputs
random-seq.out: nbody-seq
	date
	./nbody-seq 1000 1 10000 100 > random-seq.out
	date

random-par.out: nbody-par
	date
	OMP_NUM_THREADS=4 ./nbody-par 1000 1 10000 100 > random-par.out
	date

clean:
	rm -f nbody-seq nbody-par *.out *.pdf