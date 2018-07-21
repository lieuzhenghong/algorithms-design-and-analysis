#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

/** 
 * In this programming problem and the next you'll code up the clustering
 * algorithm from lecture for computing a max-spacing-clustering.

    [number_of_nodes]
    [edge 1 node 1] [edge 1 node 2] [edge 1 cost]
    [edge 2 node 1] [edge 2 node 2] [edge 2 cost]

    For example, the third line of the file is "1 3 5250", indicating that the
    distance between nodes 1 and 3 (equivalently, the cost of the edge (1,3)) is
    5250. You can assume that distances are positive, but you should NOT assume
    that they are distinct.

    Your task in this problem is to run the clustering algorithm from lecture on
    this data set, where the target number of clusters is set to 4. What is the
    maximum spacing of a 4-clustering?
*/

// Implement using a union-find dataset.
// Algorithm:
// Sort all edges.
// Maintain leader for every vertex.
// Everytime pop the topmost edge and update vertices affected.
// Keep a count of number of clusters;
// Repeat until there are only 4 clusters left.

int main() {
    const int target_clusters = 4;
    int num_clusters = 0;
    int num_vertices = 0;
    long long int max_spacing;
    int source;
    int end;
    int dist;
    std::array<int, 1000> leaders;
    //std::vector< std::array<int, 3> > edges;
    std::priority_queue< std::array<int, 3>, 
        fn(std::array<int,3>, std::array<int,3>) { return a[2] < b[2];}
    > edges;

    std::cin >> num_vertices;

    while(std::cin) {
        std::cin >> source >> end >> dist;
        edges.push({source, end, dist});
        leaders[source] = source;
        num_clusters++;
    }

    while(num_clusters > target_clusters) {
        std::cout << edges.top() << std::endl;
        end = edges.top()[1]; 
        leaders[edges.top()[0]] = end;
        // Point to new leader

        // Check if there's a decrease in clusters
        // How?
        // There should always be a decrease in clusters.
        // Consider the node N; it's always in a cluster.
        // What about an edge that's already in the cluster and forms a cycle?
        // In every r
        // Walk up until we find a reflexive vertex V that points to itself
        // Then point V to the destination vertex

        std::array<int, 3> current_v;
        std::vector<int> edges_to_update;
        while(leaders[current_v[0]] != current_v[0] ) {
            edges_to_update.push_back(current_v[0]);
            // Walk up to the next vertex new leader
            current_v = edges[current_v[1]];
        }
        // When all done, update all vertices to point to new leader
        for (auto &v : edges_to_update) {
            leaders[v[0]] = end;
        }

        // Number of clusters don't always decrease due to presence of cycles
        // After having walked the vertices, if we realise that the leader node
        // is already the desired end node, then it was a cycle.
        
        if (!cycle) {
            num_clusters--;
        }
    }

    return max_spacing;
}