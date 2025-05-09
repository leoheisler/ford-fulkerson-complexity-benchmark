# Ford-Fulkerson Tournament Benchmark

This project aims to test the complexity of the Ford-Fulkerson algorithm to apply in the tournament problem. Follow the instructions below to generate tournaments and run the benchmarks.

---

## Build tournament generator
```bash
    g++ -o build/tournament_gen tournament_generator.cpp 
    example: ./build/tournament_gen 10 > test.gr
``` 
This graph generator was built by:@mpritt
see more in: https://github.com/mrpritt/Fluxo_Maximo/blob/main/README.md

## Run graph generator script
```bash
    ./tournament_gen.sh
``` 
Note: this step may take some time 

## Run test benchmark
```bash
    ./run_tests.sh
``` 