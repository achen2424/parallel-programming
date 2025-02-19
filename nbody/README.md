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
- Run script for the three simulation configurations on the HPC cluster:
`make simulate`
- Clean up generated files:
`make clean`
- View simulation time from simulation_times.csv:
`make view`
- Generate visualization:
`make plot`

## Output Format
Each row in solar.tsv contains:
`num_particles   mass   x   y   z   vx   vy   vz   fx   fy   fz`

## Visualization
The solar.pdf file contains a multi-page visualization of planetary trajectories over time. To observe the motion properly, scroll down through the document to see how the planets evolve step by step.
 
## Benchmark Results
The following benchmarks measure execution time for three different simulation configurations.
|Number of Particles|Time Step (dt)|Iterations|Log Interval|Execution Times (milliseconds)|
|-|-|-|-|-|
|9|200|5000000|1000|2809|
|100|1|10000|100|765|
|1000|1|10000|500|72506|
