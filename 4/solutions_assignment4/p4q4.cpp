/*
In this assignment you will implement one or more algorithms for the 2SAT
problem.

The file format is as follows. The number of variables and the number of
clauses is the same, and this number is specified on the first line of the
file. Each subsequent line specifies a clause via its two literals, with a
number denoting the variable and a "-" sign denoting logical "not". For
example, the second line of the first data file is "-16808 75250", which
indicates the clause ¬_x_<sub>16808</sub> <sup>V</sup> _x_<sub>75250</sub>.

Your task is to determine if the instances is satisfiable or not. submit a 1
if the instance is satisfiable, and 0 otherwise.

DISCUSSION: This assignment is deliberately open-ended, and you can implement
whichever 2SAT algorithm you want. For example, 2SAT reduces to computing the
strongly connected components of a suitable graph (with two vertices per
variable and two directed edges per clause, you should think through the
details). This might be an especially attractive option for those of you who
coded up an SCC algorithm in Part 2 of this specialization. Alternatively,
you can use Papadimitriou's randomized local search algorithm. (The algorithm
from lecture is probably too slow as stated, so you might want to make one or
more simple modifications to it --- even if this means breaking the analysis
given in lecture --- to ensure that it runs in a reasonable amount of time.)
A third approach is via backtracking. In lecture we mentioned this approach
only in passing; see Chapter 9 of the Dasgupta-Papadimitriou-Vazirani book,
for example, for more details.
*/
/*
1. Generate the adjacency list 
2. Run Tarjan's SCC algorithm on the adjacency list
3. Examine all of the SCCs. If any SCC contains -A and A, the instance is unsatisfiable.
*/
#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <stack>
#include <climits>
#include <chrono>

typedef std::set<int> edges;
std::map<int, edges> all_edges;
int num_edges;

void dfs_stack(int start,
               std::map<int, edges> &all_edges,
               std::map<int, bool> &visited,
               std::stack<int> &stack)
{
    visited[start] = true;

    for (auto &edge : all_edges[start])
    {
        if (!visited[edge])
        {
            //std::cout << "Visiting edge " << edge << std::endl;
            dfs_stack(edge, all_edges, visited, stack);
        }
    }

    stack.push(start);
    //std::cout << "Pushed vertex " << start << " onto stack" << std::endl;
}

void dfs_scc(int start,
             std::map<int, edges> &all_edges,
             std::map<int, bool> &visited,
             edges &scc)
{
    visited[start] = true;
    for (auto &edge : all_edges[start])
    {
        if (!visited[edge])
        {
            //std::cout << "Visiting node " << edge << " from " << start << std::endl;
            dfs_scc(edge, all_edges, visited, scc);
        }
    }

    //std::cout << "Inserting node " << start << std::endl;
    scc.insert(start);
}

auto kosaraju(std::map<int, edges> all_edges)
{
    // Two passes of DFS.
    // First pass get stack
    // Second pass start from sink node to get
    std::map<int, edges> reverse_graph;
    std::vector<edges> sccs;
    std::stack<int> stack;
    std::map<int, bool> visited;

    for (auto &kv : all_edges)
    {
        //std::cout << "Now examining node " << kv.first << " which has visited: " << visited[kv.first] << std::endl;

        if (!(visited[kv.first]))
        {
            dfs_stack(kv.first, all_edges, visited, stack);
            //std::cout << visited[kv.first] << std::endl;
        }
    }

    std::cout << "Forward pass complete" << std::endl;

    // Generate the reverse graph
    for (auto &kv : all_edges)
    {
        for (auto &w : kv.second)
        {
            reverse_graph[w].insert(kv.first);
        }
    }

    // Backward DFS starting from the top of the stack
    // Reset the visited array

    std::cout << " === BACKWARD DFS === " << std::endl;
    for (auto &kv : visited)
    {
        kv.second = false;
    }
    while (!stack.empty())
    {
        int v = stack.top();
        //std::cout << "Now examining node: " << v << std::endl;
        stack.pop();
        if (!visited[v])
        {
            edges scc;
            //std::cout << "Now visiting node: " << v << std::endl;
            dfs_scc(v, reverse_graph, visited, scc);
            //std::cout << "SCC of vertex " << v << std::endl;
            /*
            for (auto &e : scc)
            {
                std::cout << e << " ";
            }
            std::cout << std::endl;
            */
            sccs.push_back(scc);
        }
    }

    std::cout << "Kosaraju's algorithm finished" << std::endl;
    return sccs;
}

void generate_adjacency_list(int v1, int v2)
{
    all_edges[-v1].insert(v2);
    all_edges[-v2].insert(v1);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    auto time_started = std::chrono::steady_clock::now();
    int v1, v2;

    std::cin >> num_edges;
    while (std::cin >> v1 >> v2)
    {
        //all_edges[v1].insert(v2);
        generate_adjacency_list(v1, v2);
    }

    std::vector<edges> sccs = kosaraju(all_edges);

    for (auto &scc : sccs)
    {
        //std::cout << "New SCC: ";
        for (auto &v : scc)
        {
            // If we can find, terminate
            if (scc.find(-v) != scc.end())
            {
                std::cout << "We have found a SCC that clashes, unsatisfiable!";
                auto time_ended = std::chrono::steady_clock::now();
                std::cout << std::endl
                          << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(time_ended - time_started).count() << std::endl;
                return 1;
            }
        }
        //std::cout << std::endl;
    }
    std::cout << "Satisfiable";
    auto time_ended = std::chrono::steady_clock::now();
    std::cout << std::endl
              << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(time_ended - time_started).count() << std::endl;

    return 0;
}
