all:
	g++ -c -O2 mergesort.cpp -o mergesort.o
	g++ -o mergesort mergesort.o

clean:
	rm -f mergesort mergesort.o

run:
	sbatch run_mergesort.sh

plot:
	python3 plot.py