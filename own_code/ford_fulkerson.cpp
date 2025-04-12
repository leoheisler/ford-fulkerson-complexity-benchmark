#include "search_algorithms.h"
#include "_Read.h"


// Ford-fulkerson algorithm
// 'graph' is the graph, s is the source and t is the sink
// calculate the max-flow
int ford_fulkerson(Graph &graph, int s, int t) {
    int n = graph.get_graph_mem().size();
    vector<int> parent(n); 
    int max_flow = 0;

    //while there is a clear path between source and sink add flow
    while (fattest_path(graph, s, t, parent)) {
        // find the max flow in found flux
        int path_flow = numeric_limits<int>::max();
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            int uv_capacity = graph.return_capacity(u,v);
            path_flow = min(path_flow, uv_capacity);
        }
        
        // update residual capacities with max flow possible in found path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            graph.update_capacity(u,v, + path_flow);
            graph.update_capacity(v,u, - path_flow);
        }
        
        // Adiciona o fluxo deste caminho ao fluxo total
        max_flow += path_flow;
    }
    
    return max_flow;
}



int main(){
    Graph g;
    unsigned edges_num, vertex_num;
    Read::read_dimacs(std::cin,vertex_num, edges_num, g);
  
    int max_flow = ford_fulkerson(g, g.get_src(), g.get_dest());

    cout << max_flow << endl;
}