#include <istream>
#include <iostream>
#include <sstream>
#include <string>
#include "_Graph.h"

class Read
{
public:
static const int INF = std::numeric_limits<int>::max();

static int read_tournament(std::istream& in, Graph& g) {
  std::string line;
  int num_teams;
  bool oh_ou = false;
  // 1) Read number of teams
  std::getline(in, line);
  std::stringstream ss(line);
  ss >> num_teams;

  // 2) Read current wins
  std::vector<int> wins(num_teams);
  std::getline(in, line);
  ss.clear(); ss.str(line);
  for (int i = 0; i < num_teams; i++) {
      ss >> wins[i];
  }

  // 3) Count games for team 1 (r1) and total game nodes
  int r1 = 0;
  // total combinations of i<j
  int total_game_nodes = (num_teams * (num_teams - 1)) / 2;
  int total_nodes = 2 + num_teams + total_game_nodes;

  // Resize graph and set source (0) / sink (1)
  g.resize_mem(total_nodes);
  g.set_src(0);
  g.set_dest(1);

  // Node indexing:
  //   0 = source, 1 = sink
  //   team nodes: 2 .. 2+num_teams-1
  //   game nodes: 2+num_teams .. total_nodes-1
  int game_node = 2 + num_teams;

  // 4) Read remaining game counts and add edges
  for (int i = 0; i < num_teams - 1; ++i) {
    std::getline(in, line);
    ss.clear(); ss.str(line);
    for (int j = i + 1; j < num_teams; ++j) {
      int g_ij;
      ss >> g_ij;
      if (g_ij > 0) {

        //should not add games to wich team 1 is playing
        if(i != 0 ){
          // source -> game node
          g.add_edge(0, game_node, g_ij);
          g.add_edge(game_node, 0, 0);
          // game node -> team i, does not add if it is the first team
          g.add_edge(game_node, 2 + i, INF);
          g.add_edge(2 + i, game_node, 0);  
          // game node -> team j
          g.add_edge(game_node, 2 + j, INF);
          g.add_edge(2 + j, game_node, 0);
        }
        // accumulate team 1 games
        if (i == 0) r1 += g_ij;
        game_node++;
      } else {
        game_node++;
      }
    }
  }
    
  // 5) Compute capacity limits m_i and add team->sink edges
  for (int i = 1; i < num_teams; i++) {
    int mi = wins[0] + r1 - wins[i] - 1;
    if (mi < 0) oh_ou = true;
    g.add_edge(2 + i, 1, mi);
    g.add_edge(1, 2 + i, 0);
  }

  return oh_ou;
}

  static void read_dimacs(std::istream& in, unsigned& vertex_num, unsigned& edges_num, Graph& g) {
    std::string line="", dummy;
    int max_c = 0;
    while (line.substr(0,5) != "p max")
      getline(in,line);
  
    // (1) get nodes and edges
    std::stringstream linestr;
    linestr.str(line);
    linestr >> dummy >> dummy >> vertex_num >> edges_num;
    g.resize_mem(vertex_num);
    unsigned i=0;
    while (i++ < edges_num) {
      getline(in,line);
      //ignore comments
      if (line.substr(0,1) == "c") i--;

      //get src & dest
      if (line.substr(0,2) == "n "){
        std::stringstream n_line(line);
        char command, font_sink;
        unsigned index;
        n_line >> command >> index >> font_sink;
        if( font_sink == 's'){
            g.set_src(index - 1);
        }else if (font_sink == 't'){
            g.set_dest(index - 1);
        }

        i--;
      }
     
      if (line.substr(0,2) == "a ") {
        std::stringstream arc(line);
        unsigned u,v,c;
        char ac;
        arc >> ac >> u >> v >> c;
        // (2) process arc (u,v) with capacity c
        g.add_edge(u - 1,v - 1,c);
        // (2.1) add reverse edge for ford-fulkerson
        g.add_edge(v - 1, u - 1, 0);
      }
    }
    g.set_max_C(g.get_src());
  }
};