#include <iostream>
#include <limits>
#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>
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
std::map<int, vector_of_edges> all_edges_leading_out_of;

/*
The following subroutine takes in  the following: 
    - Key value pair of schema:
    {
        int vertex : std:vector < std::array<double, 3> edge > edges
    }
    - An array of n length specifying the cost from the souce vertex V (set at 1)
    and every other vertex
and returns a:
    - Key value pair of that exact same schema.

How this subroutine works:

 Run through every vertex's edges. For each edge that points to it, it

Consider a path s-v. Each vertex has weight w_v.
For each edge from e that starts from a t and ends at u, add to the edge w_t - w_u.
This way, path length is invariant: the final path length is reweighted by w_s - w_v

We have a "fake" source vertex 

*/

auto johnsons (std::map<int, vector_of_edges> edges, int weights[3000] ) 
{
    for (auto &edges_from_v : edges) 
    {
        edge e;
        for (auto &edge : edges_from_v.second)
        {
            /*
            std::cout << "Old edge " << edge.source << " " <<edge.end << " " << edge.cost << std::endl;
            std::cout << "Source edge weight: " << weights[edge.source] << std::endl;;
            std::cout << "Destin edge weight: " << weights[edge.end] << std::endl;;
            */

            /*
            std::cout << "New edge " << edge.source << " " <<edge.end << " " << 
            edge.cost + weights[edge.source] - weights[edge.end]
            << std::endl;
            */

            e = {edge.source, edge.end, (edge.cost + weights[edge.source] - weights[edge.end])};
            
            all_edges_leading_out_of[edge.source].push_back(e);
        }
    }
    return all_edges_leading_out_of;
}

// Dijkstra's -- depth-first search
/*
    Algorithm as follows. Start with a source vertex in discovered.
    Whiel discovered =/= the entire graph,
    look at the smallest
*/
auto cmp (edge a, edge b) {
    return a.cost > b.cost;
}
 
auto dijkstras (int start, std::map<int, vector_of_edges> &edges) 
{

    int edge_costs[3000];
    bool discovered[3000];
    std::cout << "Running Dijkstra's from source vertex " << start << std::endl;

    for (int i = 0; i < 3000; i++) {
        edge_costs[i] = INT_MAX;
    }
    edge_costs[start] = 0;

    std::priority_queue <edge, std::vector<edge>, decltype(&cmp)> vertex_distances(cmp);

    for (auto &edge : edges[start])
    {
        //std::cout << "Pushing " << edge.source << " " << edge.end << " " << edge.cost << " " <<std::endl;
        vertex_distances.push(edge);
        int new_dist = edge_costs[edge.source] + edge.cost;
        if (edge_costs[edge.end] > new_dist) { 
            edge_costs[edge.end] = new_dist; 
            /*
            std::cout << "New distance for vertex " << edge.end << " : " << 
            edge_costs[edge.end] << std::endl;
            */
        }
    }

    // The new neighbour is the one at the top
    while (!vertex_distances.empty())
    {

        /*
        std::cout << "Vertex dist " << vertex_distances.top().source << " " 
        << vertex_distances.top().end << " "
        << vertex_distances.top().cost << std::endl;
        */

        int new_neighbour = vertex_distances.top().end;
        vertex_distances.pop();
        discovered[new_neighbour] = true;
        for (auto &edge : edges[new_neighbour])
        {
            // do the exact same thing
            int new_dist = edge_costs[edge.source] + edge.cost;
            if (edge_costs[edge.end] > new_dist) 
            { 
                edge_costs[edge.end] = new_dist; 
                vertex_distances.push( {edge.source, edge.end, edge_costs[edge.end]} );
                /*
                std::cout << "Pushing " << edge.source << " " <<
                edge.end << " " << edge_costs[edge.end] << " " <<std::endl;
                */
            }
        }
    }

    edge best_edge = {start, start, INT_MAX};
    for (int i = 0; i < num_vertices+1; i++) {
        //std::cout << "Edge cost for " << i << " : " << edge_costs[i] << std::endl;
        if (edge_costs[i] < best_edge.cost && i != start) {
            best_edge = {start, i, edge_costs[i]};
        }
    }

    return best_edge;
}


edge bellmanFord(int vertex_source) 
{
    for (int i = 0; i < 3000; i++) 
    {
        for (int j = 0; j < 3000; j++) 
        {
            costs[i][j] = INT_MAX;
        }
    }
    edge best_edge = {0, 0, INT_MAX};
    for (int i = 0; i < num_vertices+1; i++) {
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
                */
                //std::cout << "Min cost: " << costs[i-1][v] << std::endl;

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
                            << " " <<min_cost << std::endl;
                            */
                            best_edge = {vertex_source, v, min_cost};
                        }
                    }
                }
                costs[i][v] = min_cost;
                //std::cout << "Best cost: " << costs[i][v] << std::endl;
                //std::cout << "Best cost: " << costs[num_vertices-1][v] << std::endl;
            }
        }
    }

    // run again to check for negative cycles
    for (int v = 0; v < num_vertices; v++) {
        int i = num_vertices+1;
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


    // Also, let's push 0-cost edges to every vertex
    for (int v = 0; v < num_vertices+1; v++) {
        all_edges[v].push_back({0, v, 0});
    }

    // Let's sort these edges so the lowest-cost is always at the front
    for (int v = 1; v < num_vertices+1; v++) {
        std::sort(all_edges[v].begin(), all_edges[v].end(), [](edge a, edge b) {return a.cost < b.cost; });
    }

    edge best_edge = {INT_MAX, INT_MAX, INT_MAX};
    edge current_edge = bellmanFord(0);
    std::cout << current_edge.source << " " <<current_edge.end << " " 
    << current_edge.cost << std::endl;

    if (current_edge.source == -1 ) {
        std::cout << "NULL" << std::endl;
        return 1;
    }

    johnsons(all_edges, costs[num_vertices]);

    for (int i = 1; i < num_vertices+1; i++) {
        current_edge = dijkstras(i, all_edges_leading_out_of);
        current_edge.cost += costs[num_vertices][current_edge.end] -
        costs[num_vertices][current_edge.source];
        //std::cout << "Best pair: " << current_edge.source << " " <<current_edge.end << " " 
        // << current_edge.cost << std::endl;
        
        if (current_edge.cost < best_edge.cost) {
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