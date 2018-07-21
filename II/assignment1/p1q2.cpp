#include <iostream>
#include <map>
#include <vector>
#include <queue>


typedef std::array<int, 2> edge;

int main() {
  int num_verts;
  int num_edges;
  int source;
  int dest;
  int length;
  signed long long int mst_cost = 0;

  std::priority_queue <edge , std::vector <edge>, std::greater<edge> > pq;

  int vertices[1000][1000][2] = {0};
  int vertice_num_edges[1000] = {0};
  int explored_vertices[1000] = {0};

  int min_heap[1000000][2];


  std::cin >> num_verts >> num_edges;
  for (int i = 0; i < num_edges; i++) {
    int source;
    int dest;
    int length;
    std::cin >> source >> dest >> length;

    vertice_num_edges[source]++;
    vertice_num_edges[dest]++;

    vertices[source][vertice_num_edges[source]][0] = dest;
    vertices[source][vertice_num_edges[source]][1] = length;

    vertices[dest][vertice_num_edges[dest]][0] = source;
    vertices[dest][vertice_num_edges[dest]][1] = length;
  }

  // We've generated the dictionary. 
  // One-indexed.

  for (int i = 1; i < num_edges; i++) {
    for (int j = 1; j < vertice_num_edges[i]+1; j++) {
      std::cout << vertices[i][j][0] << " " << vertices[i][j][1] << std::endl;
    }
  }

  // Start from node 1

  std::vector<int> discovered_vertices(num_verts+1, 0);
  discovered_vertices[1] = 1;

  for (int i = 0; i < 1000; i++) {
    if (vertices[1][i][0] != 0) {
      pq.push({vertices[1][i][1], vertices[1][i][0]});
    }
  }

  // Push finish Node 1 into the heap

  while (!pq.empty()) {
    edge e = pq.top();
    std::cout << pq.top()[0] << " " << pq.top()[1] << std::endl;
    pq.pop();

    if (discovered_vertices[e[1]] == 0) {
      mst_cost += e[0];
      //std::cout << "New vertex " << e[1] << std::endl;
      //std::cout << "MST cost: " << mst_cost << std::endl;
      discovered_vertices[e[1]] = 1;

      for (int i = 0; i < 1000; i++) {
        if (vertices[e[1]][i][0] != 0) {
          pq.push({vertices[e[1]][i][1], vertices[e[1]][i][0]});
        }
      }
    }
  }
  std::cout << "MST cost: " << mst_cost << std::endl;
  return mst_cost;
}
