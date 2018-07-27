#include <iostream>
#include <limits>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <chrono>

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


// Implement Bellman-Ford (one pass), then implement Dijkstra's, which I've
// already coded up before in Python

// 1. Bellman-Ford
// 2. Use Johnson's algorithm to reweight vertices
// 3. Use Dijkstra's algorithm N times for each vertex

typedef std::array<double, 3> edge;
typedef std::vector<edge> vector_of_edges;

int num_vertices;
int num_edges;
double costs[3000][3000] {std::numeric_limits<double>::infinity()};
std::map<int, vector_of_edges> all_edges;

bool compLength(edge a, edge b) {
    return (a[2] < b[2]);
}

std::array<double, 3> bellmanFord(int vertex_source) {

    double best_cost = std::numeric_limits<double>::infinity();
    std::array<double , 2> best_two_pair = {0, 0};

    for (int i = 0; i < num_vertices; i++) {
        for (int v = 1; v < num_vertices+1; v++) {
            /*
            std::cout << "Currently considering the path from node " <<
            vertex_source << " to " << v << " using " << i << " edges max" <<std::endl;
            */
            if (i == 0) {
                if (v == vertex_source) {
                    costs[i][v]  = 0;
                }
                else {
                    costs[i][v] = std::numeric_limits<double>::infinity();
                }
                // std::cout << "Cost: " << costs[i][v] << std::endl;
            }
            else {
                // Two cases: either equivalent to costs[i-1][v], or equal to costs[i-1][w] + cost(w-v) for all W that point to V.
                double min_cost = costs[i-1][v];
                // std::cout << "Min cost: " << costs[i-1][v] << std::endl;
                for (int e = 0; e < all_edges[v].size(); e++) {
                    double current_cost = all_edges[v][e][2];
                    int w = all_edges[v][e][0];
                    current_cost += costs[i-1][w];
                    if (current_cost < min_cost) {min_cost = current_cost;}
                }
                costs[i][v] = min_cost;
                if (min_cost < best_cost) { 
                    best_cost = min_cost;
                    best_two_pair = {vertex_source, v};
                };
                //std::cout << "New Min cost: " << min_cost << std::endl;
            }
        }
    }

    /*
    std::cout << "Best cost: " << best_cost << std::endl;
    std::cout << "Best two pair: " << best_two_pair[0] << " , " << best_two_pair[1] << std::endl;
    */

    // Now we run with ONE more edge : i.e. i = num_vertices
    for (int v = 1; v < num_vertices+1; v++) {
        int i = num_vertices;
        /*
        std::cout << "Currently considering the path from node " <<
        vertex_source << " to " << v << " using " << i << " edges max" <<std::endl;
        */
        double min_cost = costs[i-1][v];
        //std::cout << "Min cost: " << costs[i-1][v] << std::endl;
        for (int e = 0; e < all_edges[v].size(); e++) {
            double current_cost = all_edges[v][e][2];
            int w = all_edges[v][e][0];
            current_cost += costs[i-1][w];
            if (current_cost < min_cost) {min_cost = current_cost;}
        }
        costs[i][v] = min_cost;
        // std::cout << "New Min cost: " << min_cost << std::endl;
        if (min_cost < best_cost) { 
            // std::cout << "Negative cycle detected! " << std::endl;
            return {0, 0, 0};
        }
    }
    return { best_two_pair[0] , (int)best_two_pair[1], best_cost};
}

//GOTCHAS 
// Vertices are one indexed so you have to run for loops starting from 1
//and ending at num_vertices + 1

int main() {
    std::ios_base::sync_with_stdio(false); 
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // First run Bellman-Ford. We keep a 2D array of i (number of edges we're allowed to use) and v (all vertices).
    std::cin >> num_vertices >> num_edges;

    // Fill in the edges in the following format:
    int source;
    int end;
    int cost;

    while (std::cin) {
        std::cin >> source >> end >> cost;
        edge e = {source, end, cost};
        // For each vertex, We push to array all edges that point to it
        all_edges[end].push_back(e);
        //std::cout << e[0] << " " << e[1] << " " << e[2] << std::endl;
    }

    // Let's sort these edges so the lowest-cost is always at the front
    for (int v = 1; v < num_vertices+1; v++) {
        std::sort(all_edges[v].begin(), all_edges[v].end(), compLength);
    }

    // Just for debugging purpose
    
    for (int v = 1; v < num_vertices+1; v++) {
        /*
        for (int e = 0; e < all_edges[v].size(); e++) {
            std::cout << 
            all_edges[v][e][0] << " " << 
            all_edges[v][e][1] << " " <<
            all_edges[v][e][2] << 
            std::endl;
        }
        */
    }

    // Running Bellman-Ford, let's use vertex 1 as the source.
    std::array<double, 3> best_values = {std::numeric_limits<double>::infinity()};
    for (int v = 1; v < num_vertices+1; v++) {
        std::cout << "Checking vertex " << v << std::endl;
        std::array<double,3> current_values = bellmanFord(v);
        if (current_values[0] == 0 ) {
            std::cout << "NULL" << std::endl;
            return 1;
        }
        else if (current_values[2] < best_values[2]) {
            best_values = current_values;
        }
    }

    std::cout << "BEST two pair: " << best_values[0] << " , " <<
    best_values[1] << std::endl; std::cout << "BEST cost: " << best_values[2]
    << std::endl; std::chrono::steady_clock::time_point t_end=
    std::chrono::steady_clock::now(); std::cout << "Time difference = " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(t_end -
    begin).count() <<std::endl; return 0; }