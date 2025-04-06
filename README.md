# Ford-Fulkerson Complexity Benchmark

This project aims to test the complexity of the Ford-Fulkerson algorithm using different approaches and configurations. Follow the instructions below to compile the external solver, generate graphs, and run the benchmarks.

---

## External Solver Compilation (Optional)

Use the external solver to assist with debugging. it uses boost lib

### Commands
```bash
g++ -o build/extern_solver extern_solver.cpp 
./build/extern_solver < test.gr // build < dimacs graph file
``` 
This repo uses the dimacs graph standard
See more in: https://lpsolve.sourceforge.net/5.5/DIMACS_maxf.htm

## Build graph generator
```bash
    g++ -o build/graph_gen graph_gen.c 
    example: ./build/graph_gen 1 3 3 100 test.gr
``` 
This graph generator was built by:@mpritt
see more in: https://github.com/mrpritt/Fluxo_Maximo/blob/main/README.md

## Run graph generator script
```bash
    ./graph_gen.sh
``` 
Note: this step may take some time 

## Run test benchmark
```bash
    ./run_tests.sh
``` 