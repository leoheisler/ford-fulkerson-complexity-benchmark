#include "search_algorithms.h"

/*
    FATTEST PATH

*/
bool fattest_path(Graph &residual_graph, int s, int t, std::vector<int> &parent, Logger& logger) {
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
            logger.log_fattest_itr(heap.get_num_inserts(), heap.get_num_deletes(), heap.get_num_updates());
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
    logger.log_fattest_itr(heap.get_num_inserts(), heap.get_num_deletes(), heap.get_num_updates());
    return false;
}

/*
    DFS

*/

bool dfs( Graph &residual_graph, int s, int t, vector<int> &parent, Logger& logger) {
  int n = residual_graph.get_graph_mem().size();
  vector<bool> visited(n, false);
  stack<int> st;


  int visited_vertices = 0;
  int visited_edges = 0;
  
  st.push(s);
  visited[s] = true;
  parent[s] = -1;  // src does not have a parent
  visited_vertices++;

  while(!st.empty()){
    int u = st.top();
    st.pop();

    //check for every neighbor in u
    for (const Graph::Edge& edge : residual_graph.get_neighbors(u)) {
      int target = edge.target;
      if (edge.calculate_capacity_left() > 0 ){ 
        visited_edges++;

        //check neighbor has a capacity link to v
        if (!visited[target]) {
          parent[target] = u;
          visited[target] = true;
          visited_vertices++;

          // if neighbor is sink returns true
          if (target == t){
            logger.log_iteration(visited_vertices, visited_edges);
            return true;
          } 
          st.push(target);
        }
      } 
    }
  }
  // if no path was found returns false
  logger.log_iteration(visited_vertices, visited_edges);
  return false;
}


/*
    BFS

*/
bool bfs( Graph &residual_graph, int s, int t, vector<int> &parent, Logger& logger) {
  int n = residual_graph.get_graph_mem().size();
  vector<bool> visited(n, false);
  queue<int> q;
  
  int visited_vertices = 0;
  int visited_edges = 0;

  q.push(s);
  visited[s] = true;
  parent[s] = -1;  // src does not have a parent
  visited_vertices++;

  while(!q.empty()){
    int u = q.front();
    q.pop();

    //check for every neighbor in u
    for (const Graph::Edge& edge : residual_graph.get_neighbors(u)) {
      int target = edge.target;

      if(edge.calculate_capacity_left() > 0 ){
        visited_edges++;  

        //check neighbor has a capacity link to v
        if (!visited[target]) {
          q.push(target);
          parent[target] = u;
          visited[target] = true;
          visited_vertices++;

          // if neighbor is sink returns true
          if (target == t){
            logger.log_iteration(visited_vertices, visited_edges);
            return true;
          }
        }
      }

    }
  }
  // if no path was found returns false
  logger.log_iteration(visited_vertices, visited_edges);
  return false;
}
