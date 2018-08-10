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
#include <map>
#include <set>
#include <stack>
#include <climits>

typedef std::set<int> edges;
std::map<int, edges> all_edges;
int num_edges;

void dfs_stack(int start,
               std::map<int, edges> &all_edges,
               std::array<bool, 100000> &visited,
               std::stack<int> &stack)
{
    visited[start] = true;

    for (auto &edge : all_edges[start])
    {
        if (!visited[edge])
        {
            dfs_stack(edge, all_edges, visited, stack);
        }
    }

    stack.push(start);
}

void dfs_scc(int start,
             std::map<int, edges> &all_edges,
             std::array<bool, 100000> &visited,
             edges &scc)
{
    visited[start] = true;
    for (auto &edge : all_edges[start])
    {
        if (!visited[edge])
        {
            dfs_scc(edge, all_edges, visited, scc);
        }
    }

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
    std::array<bool, 100000> visited = {0};

    // Forward path of DFS
    for (int i = 1; i <= num_edges; i++)
    {
        dfs_stack(i, all_edges, visited, stack);
    }

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
    for (bool b : visited)
    {
        b = false;
    }
    while (!stack.empty())
    {
        int v = stack.top();
        std::cout << "int v: " << v << std::endl;
        stack.pop();
        if (!visited[v])
        {
            edges scc;
            dfs_scc(v, reverse_graph, visited, scc);
            sccs.push_back(scc);
        }
    }

    return sccs;
}

int main()
{
    // generate adjacency list
    int v1, v2;
    std::cin >> num_edges;
    while (std::cin >> v1 >> v2)
    {
        all_edges[v1].insert(v2);
        all_edges[v2].insert(v1);
    }

    // run tarjan's SCCs on this adjacency list
    std::vector<edges> sccs = kosaraju(all_edges);

    // Check all SCCs: for every SCC, check that there are no occurrences of
    // its negation (for any V, check that -V not in SCC)
    for (auto &scc : sccs)
    {
        for (auto &v : scc)
        {
            std::cout << -v;
            if (scc.find(-v) != scc.end())
            {
                std::cout << "1";
                return 1;
            }
        }
    }

    std::cout << "0";
    return 0;
}