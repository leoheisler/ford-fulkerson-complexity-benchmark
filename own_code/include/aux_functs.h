#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include <complex>
#include <vector>

float max_itr_dfs(int num_edges, int num_vertex, int num_c);
float max_itr_bfs(int num_edges, int num_vertex, int num_c);
float max_itr_fattest(int num_edges, int num_vertex, int num_c);

class Logger {
  private:
      int graph_edges;
      int graph_vertices;
      int log_type;
      std::vector<float> si;
      std::vector<float> ti;
  
  public:
      Logger(int edges, int vertices, int type = 0)
          : graph_edges(edges), graph_vertices(vertices), log_type(type) {}
  
      void log_iteration(int visited_vertices, int visited_edges) {
          float s = static_cast<float>(visited_vertices) / graph_vertices;
          float t = static_cast<float>(visited_edges) / graph_edges;
          si.push_back(s);
          ti.push_back(t);
      }
  
      const std::vector<float>& get_si() const { return si; }
      const std::vector<float>& get_ti() const { return ti; }
  };

#endif
