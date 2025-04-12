#include "_Graph.h"
#include "_Heap.h"
#include <vector>
#include <stack>
#include <queue>
using namespace std;

bool fattest_path(Graph &residual_graph, int s, int t, std::vector<int> &parent);
bool dfs( Graph &residual_graph, int s, int t, vector<int> &parent);
bool bfs( Graph &residual_graph, int s, int t, vector<int> &parent);