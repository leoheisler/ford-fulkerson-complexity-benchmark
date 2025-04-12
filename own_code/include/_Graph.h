#include <vector>
#include <iostream>

class Graph {
public:
    struct Edge { 
        int target;
        int capacity;
        int used_capacity = 0;

        int calculate_capacity_left() const {
            return capacity - used_capacity;
        }
    };

private:
    int src;
    int dest;
    int num_vertex;
    int num_edges;
    std::vector<std::vector<Edge>> graph_mem;

public:
    //constructors
    Graph(): num_vertex(0), num_edges(0){}
    
    //getters & setters
    int get_num_edges() { return num_edges; }
    int get_num_vertex() { return num_vertex; }
    int get_src() { return src; }
    void set_src(int src) { this->src = src; }
    int get_dest() { return dest; }
    void set_dest(int dest) { this->dest = dest; }
    std::vector<std::vector<Edge>> get_graph_mem() { return graph_mem; }
    std::vector<Edge> get_neighbors(int i) { return graph_mem[i]; }



    //functs

    //add vertex to graph
    void add_vertex(int i) {
        std::vector<Edge> vertex = {};
        this->graph_mem[i] = vertex;
    }

    //rezie graph_memory
    void resize_mem(int n_mem) { 
        this->num_vertex = n_mem;
        graph_mem.resize(n_mem); 
    }

    //add edge to graph
    void add_edge(int source, int target, int capacity) {
        Edge new_edge = { target, capacity, 0 };
        this->num_edges++;
        graph_mem[source].push_back(new_edge);
    }

    // returns the capacity of arc u->v
    int return_capacity(int u, int v){
        for (const Edge& edge : graph_mem[u]) {
            if (edge.target == v) {
                return edge.capacity - edge.used_capacity;
            }
        }
        return 0;
    }
    

    // updates the capacity of edge u->v with value p
    void update_capacity(int u, int v, int p){
        for (Edge& edge : graph_mem[u]) {
            if (edge.target == v) {
                edge.used_capacity += p;
            }
        }
    }
    
    //prints graph
    void print_graph(){
        std::cout << "src_: " << get_src() << " dest_: " << get_dest() << std::endl;

        std::vector<Graph::Edge> edges;
        for(std::size_t  i = 0; i < graph_mem.size(); i++){
            edges = graph_mem[i];
            std::cout << "nodo: " << i + 1 << std::endl;
            for(std::size_t  j = 0; j < edges.size(); j++)
                std::cout << "   target: " << edges[j].target + 1 << " capacidade:" << edges[j].capacity << std::endl;
        }
    }
};