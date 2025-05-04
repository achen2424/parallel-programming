NVCC = nvcc
NVCC_FLAGS = -O3 -arch=sm_61
EXEC = nbody_gpu

all: $(EXEC)

$(EXEC): nbody.cpp
	$(NVCC) $(NVCC_FLAGS) nbody.cpp -o $(EXEC)

test: $(EXEC)
	chmod +x run_tests.sh
	./run_tests.sh

clean:
	rm -f $(EXEC) test_results.txt