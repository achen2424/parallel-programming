# Graph Traversal with Web API
This project performs Breadth First Search using a web based API to discover connections in a movie/actor graph.
## Overview
- Neighbors are retrieved dynamically via HTTP requests to a web API.
- The program records the execution times and prints all nodes visited up to the given depth.
## Compile and Run
To compile the graph_crawler.cpp file, run\
`make`
To view generate example test runs and view output in txt files, run\
`sbatch gc.sh`
To remove compiled files and reset the project, run:\
`make clean`