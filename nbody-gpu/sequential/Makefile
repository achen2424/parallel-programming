NVCC = nvcc
CXX = g++
CXXFLAGS = -O3 -std=c++11
NVCC_FLAGS = -O3 -arch=sm_61

EXEC_GPU = nbody_gpu
EXEC_CPU = nbody_cpu

CUDA_MODULE = module load cuda/12.4

all: $(EXEC_GPU) $(EXEC_CPU)

$(EXEC_GPU): nbody_gpu.cu
	@$(CUDA_MODULE) || true
	$(NVCC) $(NVCC_FLAGS) $< -o $@

$(EXEC_CPU): nbody_cpu.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXEC_GPU) $(EXEC_CPU) *.out