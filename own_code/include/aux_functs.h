#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include <complex>
#include <vector>
#include <numeric>

float max_itr_dfs(int num_edges, int num_vertex, int num_c);
float max_itr_bfs(int num_edges, int num_vertex, int num_c);
float max_itr_fattest(int num_edges, int num_vertex, int num_c);

class Logger {
  private:
      int graph_edges;
      int graph_vertices;
      int log_type;

      std::vector<float> inserts;
      std::vector<float> deletes;
      std::vector<float> updates;

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

    void log_fattest_itr(int inserts, int deletes, int updates){
      float insrts =  static_cast<float>(inserts) / graph_vertices;
      float updts = static_cast<float>(updates) / graph_edges;
      float delts = static_cast<float>(deletes) / graph_vertices;

      this->inserts.push_back(insrts);
      this->updates.push_back(updts);
      this->deletes.push_back(delts);
    }

    float get_si() { return accumulate(si.begin(), si.end(), 0.0f); }
    float get_ti() { return accumulate(ti.begin(), ti.end(), 0.0f); }
    float get_updates() { return accumulate(updates.begin(), updates.end(), 0.0f); }
    float get_deletes() { return accumulate(deletes.begin(), deletes.end(), 0.0f); }
    float get_inserts() { return accumulate(inserts.begin(), inserts.end(), 0.0f); }
    
  };

#endif
