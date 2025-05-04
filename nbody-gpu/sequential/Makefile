NVCC = nvcc
CXX = g++
CXXFLAGS = -O3 -std=c++11
NVCC_FLAGS = -O3 -arch=sm_61
EXEC_GPU = nbody_gpu
EXEC_CPU = nbody_cpu

all: $(EXEC_GPU) $(EXEC_CPU)

$(EXEC_GPU): nbody_gpu.cpp
	$(NVCC) $(NVCC_FLAGS) $< -o $@
$(EXEC_CPU): nbody_cpu.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXEC_GPU) $(EXEC_CPU)