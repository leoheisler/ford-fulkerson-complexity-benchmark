#include "aux_functs.h"
#include <iostream>

float max_itr_dfs(int num_edges, int num_vertex, int num_c){
  return float(num_c);
}
float max_itr_bfs(int num_edges, int num_vertex, int num_c){
  return (num_edges*num_vertex)/2;
}
float max_itr_fattest(int num_edges, int num_vertex, int num_c){
  return (num_vertex * std::log(num_c));
}