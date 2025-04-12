#include <istream>
#include <iostream>
#include <sstream>
#include <string>
#include "_Graph.h"

class Read
{
public:

  static void read_dimacs(std::istream& in, unsigned& vertex_num, unsigned& edges_num, Graph& g) {
    std::string line="", dummy;
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
  }
};