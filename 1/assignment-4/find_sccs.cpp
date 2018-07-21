// Kosaraju's two pass algorithm:
// On the first pass, run DFS on a reversed graph G_rev. Take note of the
// finishing times of every node.
//
// Relabel each node with its finishing time.
// On the second pass:
// Run DFS on the forward-but-relabeled graph G_fin, in descending order (start
// DFS call on the node that finished last).
//
// The leader call of every SCC should discover the SCC already.
// For every DFS call on G_fin_n:
//  - If every node has been explored, just pass; you are not the leader node
//    and we already have our SCC. Return the size of the explored_nodes array
//    as the size of the SCC.
//  - Otherwise, we are the leader. Do DFS, incrementing explored_nodes with
//    every node you explore.
//
// QUESTION: How do you make sure when you run DFS on the reverse graph G_rev,
// that you are able to find the first "source" node? Or will you have to
// iterate through all nodes to find the first "source" node. That looks like
// it will take O(n^2) time as there are n nodes and each call is O(n)
//
// ANSWER: Here's how we do it. 
// Loop over every single node of the graph.
// For each node, if it's explored already, skip.
// The last node to be explored is the source node.
// To see why the last node to be explored is the source node, imagine a graph
// and picking a random node to start the DFS from.
// Upon finishing the DFS:
//  - If all nodes become explored, then our DFS is finished the last node we
//    chose to explore from is (one of possibly many) source nodes.
//  - If not all nodes become explored, then we choose any one of the remaining
//    nodes to explore from. This node will definitely be a node "upstream" of
//    the previous node, as it was not reachable by the previous node. 
//  - Repeat the previous step until we have one node left: the most upstream
//    node.

#include <iostream>
#include <sstream>
#include <fstream>
#include <array>
#include <vector>
#include <string>

const int NUM_VERTICES = 875714;
typedef std::array<std::vector<int>, NUM_VERTICES> Graph;
typedef std::array<int, NUM_VERTICES> VerticeArray;
typedef std::array<bool, NUM_VERTICES> VerticeBoolArray;
// Finishing times array is, if let's say you look at the 7th element and it
// has 45569, it means that the 7th element finished 45569th.
VerticeArray finishing_times;
VerticeArray leaders;
std::vector<std::array<int, 2>> lines;
Graph graph_reversed;
Graph graph_finish_times;
VerticeBoolArray explored_list;
int finish_placing = 1;
int leader_node;

// Given a node N and a graph G, DFS will return all possible vertices within
// the graph G that can be reached from N
void dfs(int start, const Graph& graph) {
  // For edge in node;
  // Pick a random edge, then get the node of that edge
  // If there are no edges leading to unexplored nodes:
  //  backtrack
  // Else:
  //  Go to the new node pointed to by that edge and mark it 'explored'
  //  Do DFS with new_node
  explored_list[start] = true;
  leaders[leader_node]++;
  const std::vector<int>& edges = graph[start];
  for (int e : edges) {
    if (!explored_list[e]) {
      dfs(e, graph);
    }
  }
  // Iterated through all edges and all edges have been, or are, explored
  finishing_times[start] = finish_placing;
  finish_placing++;
}

// First pass: go through the nodes arbitrarily in graph_reversed
void dfs_loop_first_pass(const Graph& graph) {
  VerticeArray explored_list;
  for (int node = NUM_VERTICES; node > 1; node--) {
    if (!explored_list[node]) {
      leader_node = 0; // Just dump this away basically
      dfs(node, graph);
    }
  }
}

void dfs_loop_second_pass(const Graph& graph) {
  VerticeArray explored_list;
  for (int node = NUM_VERTICES; node > 1; node--) {
    if (!explored_list[node]) {
      leader_node = node;
      dfs(node, graph);
    }
  }
}

int main(int argc, char* argv[]) {
  // do preprocessing of the input file and populate the graph
  // for line in input (line contains s, e)
  // graph[s].push_back(e);

  if (argc < 2) {
    std::cout << "Use " << argv[0] << " " << "[filename]" << std::endl;
    return 1;
  }

  lines.push_back({0,0}); // 1-based indexing

  std::ifstream infile(argv[1]);
  std::string line, str;
  int s, e;
  // Takes "2 7" and should return ['2', '7']
  while (std::getline (infile, line)) {
    std::stringstream ss;
    ss.str(line);
    std::getline (ss, str, ' ');
    s = std::stoi(str);
    std::getline (ss, str, ' ');
    e = std::stoi(str);
    lines.push_back({s, e});
    graph_reversed[e].push_back(s);
  }
  dfs_loop_first_pass(graph_reversed);
  // Dump leaders[0]; this is the result of the first pass
  leaders[0] = 0;
  // Generate a graph labeled in order of finish times
  for (int i = 1; i < NUM_VERTICES; i++) {
    s = lines[i][0];
    e = lines[i][1];
    s = finishing_times[s];   // Relabel the vertices
    e = finishing_times[e];
    graph_finish_times[s].push_back(e);
  } 
  // Call second pass of DFS-Loop on the new graph
  dfs_loop_second_pass(graph_finish_times);

  // After calling second pass, we should have a correct leaders array
  // Look at the leaders array and get the top 5 elements
  // so just sort lor, it's a for-free primitive anyway
  // TODO
  // std::ofstream outfile("output_" + argv[1]);
  return 0;
}

