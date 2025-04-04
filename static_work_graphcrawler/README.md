# Parallel Graph Traversal with Web API
This project implements Breadth-First Search (BFS) using a web-based API to explore connections in a movie-actor graph. The traversal is optimized using multithreading to enhance performance.
## Overview
- Neighbors are retrieved dynamically via HTTP requests using libcurl.
- Parallel BFS traversal expands nodes concurrently up to a specified depth.
- Execution times are recorded, and all visited nodes are displayed.
- Error handling ensures robustness against failed HTTP requests or API errors.
- Results are outputted to text files in the output directory, listing all nodes in the specified depth and total execution time.
## Required Installations
To run this project, install RapidJSON and the libcurl library.

Clone RapidJSON to the home directory using Git:\
git clone https://github.com/Tencent/rapidjson.git

Install the libcurl library:\
Ubunut/Debian: `sudo apt install libcurl4-openssl-dev`\
MacOS: `brew install curl`

Run in HPC environment (Centaurus cluster).
## Compile and Run
To run the script in HPC environment, use: `sbatch lc.sh`\
To compile the program, run: `make`\
To execute the program: `./level_client "<Actor Name>" <depth>`\
Example: `./level_client "Tom Hanks" 2`\
This command finds all connections within 2 levels from "Tom Hanks".\
To clean up compiled files: `make clean`
