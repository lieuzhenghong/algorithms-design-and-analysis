/* 
"" In this question your task is again to run the clustering algorithm from
lecture, but on a MUCH bigger graph. So big, in fact, that the distances
(i.e., edge costs) are only defined implicitly, rather than being provided as
an explicit list.

The format is:

\[# of nodes\] \[# of bits for each node's label\] \[first bit of node 1\]
... \[last bit of node 1\] \[first bit of node 2\] ... \[last bit of node 2\]
...

For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0
1 0 1 1 0 1" denotes the 24 bits associated with node #2.

The distance between two nodes _u_ and _v_ in this problem is defined as the
Hamming distance -- the number of differing bits -- between the two nodes'
labels. For example, the Hamming distance between the 24-bit label of node #2
above and the label "0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3
(since they differ in the 3rd, 7th, and 21st bits).

The question is: what is the largest value of k such that there is a
k-clustering with spacing at least 3? That is, how many clusters are needed
to ensure that no pair of nodes with all but 2 bits in common get split into
different clusters?

NOTE: The graph implicitly defined by the data file is so big that you
probably can't write it out explicitly, let alone sort the edges by cost. So
you will have to be a little creative to complete this part of the question.
For example, is there some way you can identify the smallest distances
without explicitly looking at every pair of nodes?

""*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <string>
#include <map>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

struct node
{
    int val;
    node *leader;
};

auto convert_string_to_int(string s)
{
    //cout << s << endl;
    int i = 0;
    int n = 0;
    // Convert the string to int;

    for (auto &c : s)
    {
        if (c != ' ')
        {
            if (c == '1')
            {
                //cout << "Current n: " << n << " Current i: " << i << endl;
                n += (1 << i);
            }
            ++i;
        }
    }

    //cout << "Decimal of " << s << ": " << n << endl;
    return n;
}

void read_input(int &n, int &num_bits, vector<node> &nodes)
// Guaranteed that num_bits < 32 so it can always be stored in an int
{
    cin >> n >> num_bits;
    string tmp;
    getline(cin, tmp); //dump this \n char
    while (getline(cin, tmp))
    {
        nodes.push_back({convert_string_to_int(tmp), 0});
        // Point the node to itself
        //nodes.back().leader = &(nodes.back());
    }
}

void print_vector(vector<node> &nodes)
{
    for (auto &i : nodes)
    {
        cout << "Node: " << i.val << " Leader: " << i.leader << " with value " << (*(i.leader)).val << endl;
    }
    cout << endl;
}

auto ceildiv(int a, int b)
{
    return (a / b) + (a % b != 0);
}

// Will return -1 if it can't find the element
int binary_find(int val, vector<node> &ns)
{
    int idx = -1;
    // Binary search on &ns
    int start = 0;
    int end = ns.size() - 1;
    int mid = ceildiv(end, 2);

    // Check the "dream cases"
    if (ns[0].val == val)
    {
        return 0;
    }
    if (ns[end].val == val)
    {
        return end;
    }

    while (end - start > 1)
    {
        if (ns[mid].val > val)
        {
            end = mid;
            mid -= (end - start) / 2;
        }
        else if (ns[mid].val < val)
        {
            start = mid;
            mid += ceildiv(end - start, 2);
        }
        else
        {
            idx = mid;
            return idx;
        }
    }

    return idx;
}

int toggle_bit(int n, int k)
// Toggles the kth bit
{
    return (n ^ 1 << k);
}

auto traverse(int val, vector<node> &ns)
{
    //int idx = binary_find(val, ns);
    int idx = val;

    node *curr = &(ns[idx]);
    vector<node *> traversed_nodes;
    //cout << "Traversing node " << curr->val << " with leader " << curr->leader->val << endl;

    while (curr->leader != curr)
    {
        traversed_nodes.push_back(curr);
        curr = curr->leader;
    }

    for (auto &tn : traversed_nodes)
    {
        tn->leader = curr->leader;
    }

    return curr;
}

void cluster(int num_bits, vector<node> &ns)
{
    int id = 0;
    for (auto &n : ns)
    {
        // 1 distance
        //cout << "Now looking at node " << n.val << endl;
        for (int i = 0; i < num_bits; i++)
        {
            //cout << "Finding node " << toggle_bit(n.val, i) << endl;
            int idx = binary_find(toggle_bit(n.val, i), ns);
            if (idx != -1)
            {
                //traverse(n.val, ns)->leader = traverse(ns[idx].val, ns)->leader;
                traverse(id, ns)->leader = traverse(idx, ns)->leader;
            }
        }
        // Distance of 2

        for (int i = 0; i < num_bits; i++)
        {
            for (int j = i; j < num_bits; j++)
            {
                if (j != i)
                {
                    int tmp = toggle_bit(toggle_bit(n.val, i), j);
                    int idx = binary_find(tmp, ns);
                    if (idx != -1)
                    {
                        // traverse(n.val, ns)->leader = traverse(ns[idx].val, ns)->leader;
                        traverse(id, ns)->leader = traverse(idx, ns)->leader;
                    }
                }
            }
        }
        id++;
    }
}

void print_clusters(vector<node> &ns)
{
    int i = 0;
    for (auto &n : ns)
    {
        traverse(i, ns);
        ++i;
    }

    int num_clusters = 0;
    std::map<int, vector<int>> clusters;

    for (auto &n : ns)
    {
        clusters[n.leader->val].push_back(n.val);
    }

    cout << endl;
    cout << "Num clusters: " << clusters.size();
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int n, num_bits = 0;
    vector<node> nodes;
    read_input(n, num_bits, nodes);
    auto eq = [](node &a, node &b) { return a.val == b.val; };
    auto lt = [](node &a, node &b) { return a.val < b.val; };
    std::sort(nodes.begin(), nodes.end(), lt);
    // remove duplicates
    nodes.erase(std::unique(nodes.begin(), nodes.end(), eq), nodes.end());

    //Point each vector to itself
    for (auto &n : nodes)
    {
        n.leader = &n;
    }
    //print_vector(nodes);

    cout << "Clustering... " << endl;
    cluster(num_bits, nodes);
    //print_vector(nodes);
    print_clusters(nodes);

    std::chrono::steady_clock::time_point t_end = std::chrono::steady_clock::now();
    cout << endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - begin).count() << std::endl;

    return 0;
}