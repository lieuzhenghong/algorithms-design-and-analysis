#include <iostream>
#include <limits>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <chrono>
#include <climits>

/*
In this assignment you will implement one or more algorithms for the
all-pairs shortest-path problem.

The first line indicates the number of vertices and edges, respectively. Each
subsequent line describes an edge (the first two numbers are its tail and
head, respectively) and its length (the third number). NOTE: some of the edge
lengths are negative. NOTE: These graphs may or may not have negative-cost
cycles.

Your task is to compute the "shortest path". Precisely, you must first
identify if the graph doesn't have negative cycles. For each such graph, you
should compute all-pairs shortest paths and remember the smallest one (i.e.,
compute _min<sub>u,v ∈ V</sub>d(u,v)_, where _d(u,v)_ denotes the
shortest-path distance from _u_ to _v_).

If the graph has a negative-cost cycle, then submit "NULL" as output. Else
submit the length of its shortest path in the box below.

OPTIONAL: You can use whatever algorithm you like to solve this question. If
you have extra time, try comparing the performance of different all-pairs
shortest-path algorithms!
*/

// The smart way 
// 1. Bellman-Ford with source vertex 0 
// 2. Use Johnson's algorithm to reweight vertices
// 3. Use Dijkstra's algorithm N times for each vertex

// The naive way (this implementation)
// 1. Run Bellman-Ford n times

struct edge {
    int source;
    int end;
    int cost;
};

struct pair {
    int source;
    int end;
};


typedef std::vector<edge> vector_of_edges;

int num_vertices;
int num_edges;

int costs[3000][3000] {INT_MAX};

//double costs[3000][3000] {std::numeric_limits<double>::infinity()};
std::map<int, vector_of_edges> all_edges;

bool compLength(edge a, edge b) {
    return (a.cost < b.cost);
}

edge bellmanFord(int vertex_source) {

    for (int i = 0; i < 3000; i++) {
        for (int j = 0; j < 3000; j++) {
            costs[i][j] = INT_MAX;
        }
    }

    edge best_edge = {0, 0, INT_MAX};

    for (int i = 0; i < num_vertices; i++) {
        for (int v = 0; v < num_vertices+1; v++) {
            /*
            std::cout << "Currently considering the path from node " <<
            vertex_source << " to " << v << " using " << i << " edges max" <<std::endl;
            */
            if (i == 0) {
                if (v == vertex_source) {
                    costs[i][v]  = 0;
                }
                else {
                    costs[i][v] = INT_MAX;
                }
            }
            else {
                // Two cases: either equivalent to costs[i-1][v], or equal to costs[i-1][w] + cost(w-v) for all W that point to V.
                int prev_cost = costs[i-1][v];
                /*
                std::cout << "Current cost for pair" << vertex_source << v <<
                costs[i][v] << std::endl;
                std::cout << "Min cost: " << costs[i-1][v] << std::endl;
                */

               auto min_cost = prev_cost;

               for (auto edge : all_edges[v]) {
                    //std::cout << "Edge: " << edge.source << " " << edge.end << std::endl;
                    auto source_cost = costs[i-1][edge.source];
                    int total_cost;

                    if (source_cost == INT_MAX) {

                    }
                    else {
                        auto total_cost = source_cost + edge.cost; //w + c(w-v)
                        if (total_cost < min_cost) {
                            min_cost = total_cost;
                        }
                        if (min_cost < best_edge.cost) {
                            /*
                            std::cout << "Best edge found!" << vertex_source << " " << v 
                            << " " <<min_cost
                            << std::endl;
                            */
                            best_edge = {vertex_source, v, min_cost};
                        }
                    }
                }
                costs[i][v] = min_cost;
                //std::cout << "Best cost: " << costs[i][v] << std::endl;
            }
        }
    }

    // run again to check for negative cycles
    for (int v = 0; v < num_vertices; v++) {
        int i = num_vertices;
        // For all edges that point to the vertex
        for (auto edge : all_edges[v]) {
            if (costs[i-1][edge.source] != INT_MAX && 
            (costs[i-1][edge.source] + edge.cost) < best_edge.cost) {
                std::cout << "There's a negative cycle!" << std::endl;
                return {-1, -1, INT_MAX};
            }
        }
    }


    /*
    std::cout << "Best edge: " << best_edge.source << " " << best_edge.end <<
    " " << best_edge.cost << std::endl;
    */

    return best_edge;
}

//GOTCHAS 
// Vertices are one indexed so you have to run for loops starting from 1
//and ending at num_vertices + 1

int main() {
    std::ios_base::sync_with_stdio(false); 
	auto time_started = std::chrono::steady_clock::now();
    // First run Bellman-Ford. We keep a 2D array of i (number of edges we're allowed to use) and v (all vertices).
    std::cin >> num_vertices >> num_edges;

    // Fill in the edges in the following format:
    edge e;

    while (std::cin >> e.source >> e.end >> e.cost) {
        // For each vertex, We push to array all edges that point to it
        all_edges[e.end].push_back(e);
        //std::cout << e[0] << " " << e[1] << " " << e[2] << std::endl;
    }

    // Let's sort these edges so the lowest-cost is always at the front
    for (int v = 1; v < num_vertices+1; v++) {
        std::sort(all_edges[v].begin(), all_edges[v].end(), compLength);
    }

    // We run Bellman-Ford's algorithm n times to final the shortest pair ever
    //std::array<double, 3> best_values = {std::numeric_limits<double>::infinity()};
    edge best_edge = {INT_MAX};

    for (int v = 1; v < num_vertices+1; v++) {
        std::cout << "Checking vertex " << v << std::endl;
        edge current_edge = bellmanFord(v);
        /*
        std::cout << current_edge.source << " " <<current_edge.end << " " 
        << current_edge.cost << std::endl;
        */
        if (current_edge.source == -1 ) {
            std::cout << "NULL" << std::endl;
            return 1;
        }
        else if (current_edge.cost < best_edge.cost) {
            best_edge = current_edge;
        }
    }

    std::cout << "BEST two pair: " << best_edge.source << " , " << best_edge.end << std::endl;
    std::cout << "BEST cost: " << best_edge.cost << std::endl;

    auto time_ended = std::chrono::steady_clock::now();

    std::cout << "Time difference = " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(time_ended -
    time_started).count() <<std::endl;

    return 0;
}