#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <set>
#include <stack>
#include <climits>
#include <queue>
#include <chrono>

typedef std::set<int> edges;
std::map<int, edges> all_edges;
int num_edges;
auto time_started = std::chrono::steady_clock::now();

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

auto kosaraju(std::map<int, edges> &all_edges)
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
    auto forward_pass = std::chrono::steady_clock::now();
    std::cout << "Forward pass time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(forward_pass - time_started).count() << std::endl;

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
    auto time_ended = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(time_ended - time_started).count() << std::endl;

    return sccs;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int v1, v2;
    std::priority_queue<int> five_largest_sccs;

    while (std::cin >> v1 >> v2)
    {
        all_edges[v1].insert(v2);
    }

    std::vector<edges> sccs = kosaraju(all_edges);

    for (auto &scc : sccs)
    {
        /*
        std::cout << "New SCC: ";
        for (auto &v : scc)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
        //std::cout << "Size of SCC: " << scc.size() << std::endl;
        */
        five_largest_sccs.push(scc.size());
    }

    // Print out 5 largest SCCs
    std::cout << "Five largest SCCS: ";
    for (int i = 0; i < 5; i++)
    {
        if (five_largest_sccs.empty())
        {
            std::cout << "0";
        }
        else
        {
            std::cout << five_largest_sccs.top() << " ";
            five_largest_sccs.pop();
        }
    }

    auto time_ended = std::chrono::steady_clock::now();
    std::cout << std::endl
              << "Time difference = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(time_ended - time_started).count();

    return 0;
}