#include "search_algorithms.h"
#include "_Read.h"
#include <chrono>
#include <fstream>
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
    //start instances    
    Graph g; 
   
    bool oh_ou = Read::read_tournament(std::cin,g);
    if(oh_ou){
      cout << "nao vai ta dando" << endl;
    }else{
      cout << "executando ford-fulkerson" << endl;
    }
    /*        
    Logger l(g.get_num_edges(), g.get_num_vertex(), fulkerson_family);
    std::ofstream csv_file;

    if( outfile != "" ) {
      csv_file.open(outfile, std::ios::app);

      if (!csv_file.is_open()) {
        std::cerr << "Error opening csv_file\n";
        return 1;
      }   
    }


    //get limits
    LimitCalc arr[] = {max_itr_fattest, max_itr_bfs, max_itr_dfs};
    limit_calc = arr[fulkerson_family];
    float limit = limit_calc(g.get_num_edges(), g.get_num_vertex(), g.get_max_c());

    //call functs && get duration
    auto start = high_resolution_clock::now();
    int max_flow = ford_fulkerson(g, g.get_src(), g.get_dest(), l);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    //print results
    cout << max_flow << endl;

    /* DATA ANALISIS FOR FF FUNCTS */
    //pessimistic complexity calc
    /*
    long long tempo_ns = duration.count();
    long long n = g.get_num_vertex();
    long long m = g.get_num_edges();

    long long complexity = n * m * (n + m);

    // real_time / complexity
    double real_over_theoretical = (double)tempo_ns / complexity;

    auto si_l = l.get_si() / g.get_num_itr();
    auto ti_l =  l.get_ti() / g.get_num_itr();

    if(csv_file.is_open()){
      csv_file << test_file << ",";
      csv_file << g.get_num_vertex() << ",";
      csv_file << g.get_num_edges() << ",";
      csv_file << g.get_num_itr() << ",";
      csv_file << limit << ",";
      csv_file << g.get_num_itr() / limit << ',';
      csv_file << si_l << ',';
      csv_file << ti_l << ',';
      csv_file << l.get_inserts() / g.get_num_itr()  << ',';
      csv_file << l.get_deletes() / g.get_num_itr() << ',';
      csv_file << l.get_updates() / g.get_num_itr() << ',';
      csv_file << smallest_path << ',';
      csv_file << si_l*g.get_num_vertex() + ti_l*g.get_num_edges() + accumulate(hops_per_itr.begin(), hops_per_itr.end(), 0) << ',';
      csv_file << duration.count()/1e6 << ",";
      csv_file << real_over_theoretical << '\n';

      csv_file.close();
    }
  */
}