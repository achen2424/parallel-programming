# CUDA-Based Parallel N-Body Simulation in C++
## Overview
This project implements gravitational N-body simulations in both sequential (CPU) and parallel (GPU/CUDA) versions, comparing their performance.
## Contents
- `nbody_cpu.cpp`: Sequential CPU implementation
- `nbody_gpu.cu`: Parallel GPU implementation using CUDA
- `tests.sh`: SLURM script for benchmarking
- `output.txt`: Sample benchmark results

## Features
- Simulates gravitational interactions between N particles
- Supports:
  - Random particle initialization
  - Predefined solar system configuration (`planet`)
  - Loading from input files
- GPU version accelerates computation using CUDA kernels

## Compilation
### CPU version
`g++ nbody_cpu.cpp -o nbody_cpu -O3`

### GPU version (requires CUDA)
`nvcc nbody_gpu.cu -o nbody_gpu -O3 -arch=sm_61`

## Usage
CPU Version
`./nbody_cpu <input> <dt> <steps> <print_every>`
GPU Version
`./nbody_gpu <input> <dt> <steps> <print_every> <block_size>`

- input: Number of particles, planet, or input filename
- dt: Time step size
- steps: Number of simulation steps
- print_every: Output interval (0 to disable)
- block_size: CUDA thread block size (e.g., 128, 256, 512)

## Example Benchmarks
Use `sbatch tests.sh` to run given test cases for GPU and CPU.\
Manual test examples:
`./nbody_cpu 20000 0.1 100 0`
`./nbody_gpu 20000 0.1 100 0 256`

## Results
See output.txt for example timings.
