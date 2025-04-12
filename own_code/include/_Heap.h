#include <vector>
#include <unordered_map>
#include <cmath>

class Heap {

struct Node{
    unsigned capacity;
    unsigned vertex;
};

private:
    //control vars
    int k;

    std::vector<Node> heap_queue = {};
    std::unordered_map<int,int> vertex_heap_map;

    /*  PRIVATE FUNCTS */
    // Returns parent heap index
    // of child i
    int get_parent_index(int i) {
        return (i - 1) / k;
    }

    // Returns child node heap j index
    // if j == 2, returns second child from 
    // i parent
    int get_child_index(int i, int j) {
        return k * i + j + 1; 
    }
    
    // Reorders heap to preserve min_heap property
    // swaps child and father priority, sending child up
    // return number of sifts
    void sift_up(int child_index) {
        while (child_index > 0 && heap_queue[child_index].capacity > heap_queue[get_parent_index(child_index)].capacity) {
            std::swap(heap_queue[child_index], heap_queue[get_parent_index(child_index)]);

            //swap mapping values
            vertex_heap_map[heap_queue[child_index].vertex] = child_index;
            vertex_heap_map[heap_queue[get_parent_index(child_index)].vertex] = get_parent_index(child_index);

            child_index = get_parent_index(child_index);
        }
    }

    // Reorders heap to preserve min_heap property
    // swaps child and father priority, sending father up
    // return number of sifts
    void sift_down(int parent_index) {
        int smallest_index = parent_index;

        //check if any children has a smaller capacity
        for (int j = 0; j < k; ++j) {
            int c = get_child_index(parent_index, j);
            if (size_t(c) < heap_queue.size() && heap_queue[c].capacity > heap_queue[smallest_index].capacity) {
                smallest_index = c;
            }
        }

        if (smallest_index != parent_index) {
            std::swap(heap_queue[parent_index], heap_queue[smallest_index]);

            //swap mapping values
            vertex_heap_map[heap_queue[parent_index].vertex] = parent_index;
            vertex_heap_map[heap_queue[smallest_index].vertex] = smallest_index;
            sift_down(smallest_index);
        }

    }
public:
    //contructor
    Heap(int k): k(k) {}

    //heap functions
    //Inserts node in heap 
    void insert(unsigned capacity, unsigned vertex) {

        if (vertex_heap_map.count(vertex)) {
            //update capacity if vertex is already in heap
            if (capacity < heap_queue[vertex_heap_map[vertex]].capacity) {

                heap_queue[vertex_heap_map[vertex]].capacity = capacity;

                sift_up(vertex_heap_map[vertex]);
            }
        } else {

            Node new_vertex = {capacity,vertex};
            heap_queue.push_back(new_vertex);
            
            int new_vertex_index = heap_queue.size() - 1;
            vertex_heap_map[vertex] = new_vertex_index;

            sift_up(new_vertex_index);
        }
    }
    
    //extract min
    Node extract_max() {
        
        //release first node
        Node min_node = heap_queue[0];
        vertex_heap_map.erase(min_node.vertex);

        //send last node to first position
        heap_queue[0] = heap_queue.back();
        vertex_heap_map[heap_queue[0].vertex] = 0;
        
        //destroy last position
        heap_queue.pop_back();

        if (!heap_queue.empty()) {
            sift_down(0);
        }

        return min_node;
    }

    // Returns heap state
    bool is_empty() {
        return heap_queue.empty();
    }
    
};
