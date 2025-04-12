#include "_Read.h"

int main(){
    Graph g;
    unsigned edges_num, vertex_num;
    Read::read_dimacs(std::cin,vertex_num, edges_num, g);
  
    g.print_graph();
}