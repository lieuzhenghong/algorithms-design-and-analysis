#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <chrono>

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

typedef std::array<int, 3> edge;

const int MAX_VERTS = 2000;

// This function, when run on a vertex v, guarantees that it and all its parents
// will point to its root leader.
void compress(std::array <int, MAX_VERTS>& leaders, int v) {
    std::vector<int> vs_to_update;
    int curr_v = v;	

    // Walk up the vertex tree until we find the leader (vert points to itself)
    while(leaders[curr_v] != curr_v) {
		//std::cout << "Current vertex: " << curr_v << " pointing to " << leaders[curr_v] << std::endl;
        vs_to_update.push_back(curr_v);
        curr_v = leaders[curr_v];
    }

    // Now compress all vertices
    for (auto w : vs_to_update) {
        //std::cout << "Updating vertex " << w << " to point at " << curr_v << std::endl;
        leaders[w] = curr_v;
    }
}

int main() {
    const int target_clusters = 4;
    int num_clusters = 0;
    int num_vertices = 0;

    int source;
    int end;
    int dist;

    int max_dist;
    std::array <int, MAX_VERTS> leaders;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for (int i = 0; i < MAX_VERTS; i++) {
		leaders[i] = i;
	}

    auto cmp = [](edge a, edge b) { return (a[2] > b[2]); };

    std::priority_queue <
        edge,
        std::vector<edge>,
        decltype(cmp)
    > edges(cmp);

    std::cin >> num_vertices;
	num_clusters = num_vertices;

    while(std::cin) {
        std::cin >> source >> end >> dist;
        //std::cout << source << " " << end << " " << dist << std::endl;
        edges.push({source, end, dist});
        leaders[source] = source;
    }

    // Why >= ? Because we want to stop at the node that brings it from
    // four clusters to three, as that's the maximum distance between
    // vertices that's not in a cluster.

    while (num_clusters >= target_clusters) {
        //std::cout << "Number of clusters: " << num_clusters << std::endl;

        source = edges.top()[0];
        end = edges.top()[1];
        dist = edges.top()[2];

        edges.pop();

		//std::cout << source << " " << end << " " << dist << std::endl;

        // Compress END: now guaranteed it points to LEADER(END)
        //std::cout << "Compressing leader..." << std::endl;
        compress(leaders, end);
        // Compress SOURCE

		/*
		std::cout << "leaders after end compression: " << std::endl;
		for (int i = 1; i < num_vertices+1; i++) {
			std::cout << leaders[i] << " ";
		}
		std::cout << std::endl;

        std::cout << "Compressing source..." << std::endl;
		*/
        compress(leaders, source);

        // Now we have a guarantee that source and end both point to root leader
        // By comparing the source's leader to the end's leader, we can tell if
        // they are already in the same cluster.
        // if they are not identical, point the source leader to end leader, clusters--

        if (leaders[source] != leaders[end]) {
            leaders[leaders[source]] = leaders[leaders[end]];
            max_dist = dist;
            num_clusters--;
        }
    }

	std::cout << "Max distance: " << max_dist << std::endl;
	std::chrono::steady_clock::time_point t_end= std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(t_end - begin).count() <<std::endl;
    return max_dist;
}



