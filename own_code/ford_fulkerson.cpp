#include "search_algorithms.h"
#include "_Read.h"
#include <chrono>
#include <fstream>
using namespace std::chrono;

typedef bool (*PathFinder)(Graph&, int, int, vector<int>&, Logger&);
typedef float (*LimitCalc)(int, int, int);

vector<int> hops_per_itr;
int smallest_path = INT8_MAX;
int fulkerson_family = 0;

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
// int, should output timinings
// ex: ./build/ford_fulkerson 
int main(int argc, char* argv[]){ 
    //start instances 
    bool should_doc_time = false ;
    if (argc > 1){
      should_doc_time = atoi(argv[1]);
    }  
    Graph g; 
    string outfile = "./results/timings.csv";
    fulkerson_family = 0;

    Logger l(g.get_num_edges(), g.get_num_vertex(), fulkerson_family);
    std::ofstream csv_file;

    if( outfile != "" ) {
      csv_file.open(outfile, std::ios::app);

      if (!csv_file.is_open()) {
        std::cerr << "Error opening csv_file\n";
        return 1;
      }   
    }

    auto start = high_resolution_clock::now();
    bool oh_ou = Read::read_tournament(std::cin,g);
    //g.print_graph();
    if(oh_ou){
      cout << "nao" << endl;
    }else{
      int max_flow = ford_fulkerson(g, g.get_src(), g.get_dest(), l);

      if( max_flow == g.get_total_games()){
        cout << "sim" << endl;
      }else{
        cout << "nao" << endl;
      }
    }
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(stop - start);

    /* stores timings in the csv_file */
    
    long long tempo_ns = duration.count();

    if(csv_file.is_open() && should_doc_time){
      csv_file << g.get_num_teams() << ",";
      csv_file << duration.count()/1e6 << ",";
      csv_file << tempo_ns << endl;

      csv_file.close();
    }
}