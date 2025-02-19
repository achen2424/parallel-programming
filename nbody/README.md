# N-Body Simulation

## Overview
This project implements an N-Body Simulation in C++ to model the gravitational interactions between celestial bodies. The simulation follows Newtonian mechanics and computes forces, velocities, and positions over time.

## Features
- Simulates planetary motion using Newton’s Law of Gravitation
- Allows random initialization for arbitrary numbers of particles
- Optimized force calculations with a softening factor to prevent numerical instability
- Outputs results in TSV format for visualization with plot.py
- Supports both local execution and HPC cluster execution (Slurm)

## Compile and Execute
- Compile the simulation:
`make`
- Run an example simulation locally:
`make run_local`
- Run on the HPC cluster:
`make simulate`
- Clean up generated files:
`make clean`
- View simulation time log:
`make view`
- Generate visualization:
`make plot`

## Output Format
Each row in solar.tsv contains:
`num_particles   mass   x   y   z   vx   vy   vz   fx   fy   fz`
 
## Benchmark
9 particles (sun and 8 planets), 200 dt, 5000000 steps, 1000 log interval:/
Execution time: 17 seconds
100 particles, 1 dt, 10000 steps, 100 log interval:/
Execution time: 4 seconds
1000 particles, 1 dt, 10000 steps, 500 log interval:/
Execution time: 413 seconds