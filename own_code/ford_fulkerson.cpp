#include "search_algorithms.h"
#include "_Read.h"
#include <chrono>
using namespace std::chrono;

vector<int> hops_per_itr;
int smallest_path = INT8_MAX;
int fulkerson_family = 0;
typedef bool (*PathFinder)(Graph&, int, int, vector<int>&, Logger&);
typedef float (*LimitCalc)(int, int, int);

// Ford-fulkerson algorithm
// 'graph' is the graph, s is the source and t is the sink
// calculate the max-flow
int ford_fulkerson(Graph &graph, int s, int t, Logger &logger) {
    int path = 0;
    int n = graph.get_graph_mem().size();
    PathFinder path_finder = nullptr;
    vector<int> parent(n); 
    int max_flow = 0;
    int i = 1; 

    // choose path_finder funct based on entry
    PathFinder arr[] = {fattest_path, bfs, dfs};
    path_finder = arr[fulkerson_family];

    //while there is a clear path between source and sink add flow
    while (path_finder(graph, s, t, parent, logger)) {
        i++;
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
            path++;
            graph.update_capacity(u,v, + path_flow);
            graph.update_capacity(v,u, - path_flow);
        }
         
        // Add flux to total flow
        max_flow += path_flow;

        //update smallest path found
        if(path < smallest_path){
          smallest_path = path;
        }
        hops_per_itr.push_back(path);
        path = 0;
    }
    graph.set_num_itr(i);
    return max_flow;
}
// ARGV ENTRIES (ordered)
// int fulkerson_family < enum for function chose, 0 = fattest, 1 = bfs, 2 = dfs, 3+ error
// char* outfile < file where values of tests will be stored
// char* test_file < test file name
// ex: ./build/ford_fulkerson 1 test.csv test.gr < test.gr
// OR, without any parameter, just prints max_flow
// ex: ./build/ford_fulkerson
int main(int argc, char* argv[]){
    LimitCalc limit_calc = nullptr;
    string test_file = "";
    string outfile = "";
    if( argc >= 2 ){
      fulkerson_family = atoi(argv[1]);
      outfile = argv[2];
      test_file = argv[3];
    }
    Graph g;
    unsigned edges_num, vertex_num;
    Read::read_dimacs(std::cin,vertex_num, edges_num, g);
    Logger l(g.get_num_edges(), g.get_num_vertex(), fulkerson_family);

    //get limits
    LimitCalc arr[] = {max_itr_fattest, max_itr_bfs, max_itr_dfs};
    limit_calc = arr[fulkerson_family];
    float limit = limit_calc(g.get_num_edges(), g.get_num_vertex(), g.get_max_c());

    //call functs && get duration
    auto start = high_resolution_clock::now();
    int max_flow = ford_fulkerson(g, g.get_src(), g.get_dest(), l);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    //print results

    auto si_l = l.get_si() / g.get_num_itr();
    auto ti_l =  l.get_ti() / g.get_num_itr();
    cout << max_flow << endl;
    cout << duration.count() << "ms" << endl;
    cout << duration.count() /( g.get_num_edges() * g.get_num_vertex() * ( g.get_num_edges() + g.get_num_vertex())) << endl;
    cout << g.get_num_itr() / limit << endl;
    cout << si_l << endl;
    cout << ti_l << endl;
    cout << l.get_inserts() / g.get_num_itr() << endl;
    cout << l.get_deletes() / g.get_num_itr() << endl;
    cout << l.get_updates() / g.get_num_itr() << endl;
    cout << smallest_path << endl;
    cout << si_l*g.get_num_vertex() + ti_l*g.get_num_edges() + accumulate(hops_per_itr.begin(), hops_per_itr.end(), 0);


}