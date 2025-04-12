#include "_Read.h"
#include "_Heap.h"
#include <vector>
#include <queue>
#include <stack>
#include <limits>


using namespace std;

/*
    FATTEST PATH

*/
bool fattest_path(Graph &residual_graph, int s, int t, std::vector<int> &parent) {
    int n = residual_graph.get_graph_mem().size();

    // vector holding the max capacity to each vertex
    std::vector<int> max_cap(n, 0);

    // create binary heap
    Heap heap(2);
    
    // max_capacity for source
    max_cap[s] = std::numeric_limits<int>::max();
    heap.insert(max_cap[s], s);

    while (!heap.is_empty()) {
        //extract max_capacity
        auto node = heap.extract_max();
        int u = node.vertex;
        int cap_u = node.capacity;

        //if u is sink, we found the max capacity due to heap action
        if (u == t) {
            return true;
        }

        // visit each vertex neighbor of u
        for (const auto &edge : residual_graph.get_neighbors(u)) {
            int v = edge.target;
            int cap_left = edge.calculate_capacity_left();
            if (cap_left > 0) {
                // max-min capacity for u
                int new_cap = std::min(cap_u, cap_left);
                if (new_cap > max_cap[v]) {
                    max_cap[v] = new_cap;
                    parent[v] = u;
                    heap.insert(new_cap, v);  // insert value in heap
                }
            }
        }
    }

    return false;
}

/*
    DFS

*/
bool dfs( Graph &residual_graph, int s, int t, vector<int> &parent) {
    int n = residual_graph.get_graph_mem().size();
    vector<bool> visited(n, false);
    stack<int> st;
    
    st.push(s);
    visited[s] = true;
    parent[s] = -1;  // src does not have a parent

    while(!st.empty()){
        int u = st.top();
        st.pop();

        //check for every neighbor in u
        for (const Graph::Edge& edge : residual_graph.get_neighbors(u)) {
            int target = edge.target;
            //check neighbor has a capacity link to v
            if (!visited[target] && edge.calculate_capacity_left() > 0) {
                parent[target] = u;
                visited[target] = true;
                // if neighbor is sink returns true
                if (target == t) 
                    return true;
                st.push(target);
            }
        }
    }
    // if no path was found returns false
    return false;
}
/*
    bfs

*/
bool bfs( Graph &residual_graph, int s, int t, vector<int> &parent) {
    int n = residual_graph.get_graph_mem().size();
    vector<bool> visited(n, false);
    queue<int> q;
    
    q.push(s);
    visited[s] = true;
    parent[s] = -1;  // src does not have a parent

    while(!q.empty()){
        int u = q.front();
        q.pop();

        //check for every neighbor in u
        for (const Graph::Edge& edge : residual_graph.get_neighbors(u)) {
            int target = edge.target;
            //check neighbor has a capacity link to v
            if (!visited[target] && edge.calculate_capacity_left() > 0) {
                q.push(target);
                parent[target] = u;
                visited[target] = true;
                // if neighbor is sink returns true
                if (target == t) 
                    return true;
            }
        }
    }
    // if no path was found returns false
    return false;
}

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