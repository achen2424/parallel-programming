# Graph Traversal with Web API
This project performs Breadth First Search using a web based API to discover connections in a movie/actor graph.
## Overview
- Neighbors are retrieved dynamically via HTTP requests to a web API.
- BFS traversal is performed to a given depth.
- Execution times are recorded and all visited nodes are printed.
- Results are outputted to text files and all reachable nodes will be listed within the given depth from the start node.

## Required Installations
To run this project, install RapidJSON and the libcurl library.

Clone RapidJSON to the home directory using Git:\
git clone https://github.com/Tencent/rapidjson.git

Install the libcurl library:\
Ubunut/Debian: `sudo apt install libcurl4-openssl-dev`\
MacOS: `brew install curl`

Run in HPC environment (Centaurus cluster).
## Compile and Run
To compile the graph_crawler.cpp file, run:\
`make`

To manually run the program, use:\
`./gc <Actor Name> <node-depth>`

To generate example test runs in txt files located in output directory, run:\
`sbatch gc.sh`

To remove compiled files and reset the project, run:\
`make clean`
