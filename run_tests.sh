#!/bin/bash

mkdir -p results/fattest

echo "doing fattest_path_tests"

declare -A graph_sets=(
  ["line_graphs"]="fattest_linegraph.csv"
  ["mesh_graphs"]="fattest_meshgraphs.csv"
  ["rand2_graphs"]="fattest_rand2graphs.csv"
)

header="FILE_NAME,VERTEX_NUM,EDGES_NUM,ITERATIONS,LIMIT,ITERATION_RATIO,SI,TI,INSERTS,DELETES,UPDATES,SMALLEST_PATH,APPROXIMATION,DURATION,DURATION_COMPLEXITY_RATIO"

for graph_type in "${!graph_sets[@]}"; do
  dir="./graphs/$graph_type"
  outfile="results/fattest/${graph_sets[$graph_type]}"

  echo "$header" > "$outfile"
  echo "    doing ${graph_type} tests"

  while IFS= read -r graph_file; do
    echo "   test for ${graph_file}"
    ./build/ford_fulkerson "0" "$outfile" "$graph_file" < "$graph_file"
  done < <(find "$dir" -type f)
done

#####################################################################

mkdir -p results/dfs

echo "doing dfs_path_tests"

declare -A graph_sets=(
  ["line_graphs"]="dfs_linegraph.csv"
  ["mesh_graphs"]="dfs_meshgraphs.csv"
  ["rand2_graphs"]="dfs_rand2graphs.csv"
)

header="FILE_NAME,VERTEX_NUM,EDGES_NUM,ITERATIONS,LIMIT,ITERATION_RATIO,SI,TI,INSERTS,DELETES,UPDATES,SMALLEST_PATH,APPROXIMATION,DURATION,DURATION_COMPLEXITY_RATIO"

for graph_type in "${!graph_sets[@]}"; do
  dir="./graphs/$graph_type"
  outfile="results/dfs/${graph_sets[$graph_type]}"

  echo "$header" > "$outfile"
  echo "    doing ${graph_type} tests"

  while IFS= read -r graph_file; do
    echo "   test for ${graph_file}"
    ./build/ford_fulkerson "2" "$outfile" "$graph_file" < "$graph_file"
  done < <(find "$dir" -type f)
done

#######################################################################################
mkdir -p results/bfs

echo "doing bfs_path_tests"

declare -A graph_sets=(
  ["line_graphs"]="bfs_linegraph.csv"
  ["mesh_graphs"]="bfs_meshgraphs.csv"
  ["rand2_graphs"]="bfs_rand2graphs.csv"
)

header="FILE_NAME,VERTEX_NUM,EDGES_NUM,ITERATIONS,LIMIT,ITERATION_RATIO,SI,TI,INSERTS,DELETES,UPDATES,SMALLEST_PATH,APPROXIMATION,DURATION,DURATION_COMPLEXITY_RATIO"

for graph_type in "${!graph_sets[@]}"; do
  dir="./graphs/$graph_type"
  outfile="results/bfs/${graph_sets[$graph_type]}"

  echo "$header" > "$outfile"
  echo "    doing ${graph_type} tests"

  while IFS= read -r graph_file; do
    echo "   test for ${graph_file}"
    ./build/ford_fulkerson "1" "$outfile" "$graph_file" < "$graph_file"
  done < <(find "$dir" -type f)
done
