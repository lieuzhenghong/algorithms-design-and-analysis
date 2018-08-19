/*

In this programming problem you'll code up the dynamic programming algorithm for computing a maximum-weight independent set of a path graph.

 The input file describes the weights of the vertices in a path graph (with the weights listed in the order in which vertices appear in the path). It has the following format:

 \[number_of_vertices\]
 \[weight of first vertex\]
 \[weight of second vertex\]
 ...

 For example, the third line of the file is "6395702," indicating that the weight of the second vertex of the graph is 6395702.

 Your task in this problem is to run the dynamic programming algorithm (and the reconstruction procedure) from lecture on this data set. The question is: of the vertices 1, 2, 3, 4, 17, 117, 517, and 997, which ones belong to the maximum-weight independent set? By "vertex 1" we mean the first vertex of the graph -- there is no vertex 0--.

 The output is a 8-bit string, where the _i<sup>th</sup>_ bit should be 1 if the _i<sup>th</sup>_ of these 8 vertices is in the maximum-weight independent set, and 0 otherwise. For example, if you think that the vertices 1, 4, 17, and 517 are in the maximum-weight independent set and the other four vertices are not, then you should enter the string 10011010 in the box below.

 **NOTE**: If the graph doesn't have a node, then it doesn't belong to the maximum-weight independent set, and therefore its bit would be 0. For example, if the size of the graph is 500, then the two last bits correspondning to nodes 517 and 997 would be 0.

*/

/*
To calculate a maximum-weight independent set, we rely on the following decomposition:

Consider the set S = {a, b, c, ..., u, v, w}

Consider the wts S' of S. There are two possibilities:
1. w not in S'
2. w in S'.

Case 1. (w not in S').
If w not in S', we can reduce the problem right away.
    wts[S] = wts[S-{w}]

Case 2. (w in S').

If w in S', two possibilities: either 
    * wts[S] = wts[S-{w - v}] + weight(w), or
    * wts[S] = wts[S-{w}] (which we know includes v).

Consider the special cases:
wts( of length 0 ) = 0;
wts([a]) = a;

For everything else, wts[S] = max {
    wts[S-last],
    wts[S-last 2 elements] + last
}

*/

#include <iostream>
#define ll long long
const int MAX_VERTS = 100000;

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

int main()
{
    ll wts[MAX_VERTS + 1] = {0};
    bool mwis[MAX_VERTS + 1] = {0};
    ll wt;
    int counter = 0;
    int num_verts;
    std::cin >> num_verts;
    while (std::cin >> wt)
    {
        counter++;
        if (counter == 1)
        {
            wts[counter] = wt;
        }
        else
        {
            wts[counter] = max(wts[counter - 1], wts[counter - 2] + wt);
        }
    }

    // walk through the array backwards to generate the MWIS
    int j = num_verts;
    while (j > 0)
    {
        if (wts[j] != wts[j - 1])
        {
            mwis[j] = true;
            j -= 2;
        }
        else
        {
            mwis[j] = false;
            j--;
        }
    }

    /*

    std::cout << "Weights: ";
    for (int i = 1; i <= num_verts; i++)
    {
        std::cout << wts[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "MWIS: ";
    for (int i = 1; i <= num_verts; i++)
    {
        std::cout << mwis[i] << " ";
    }
    std::cout << std::endl;

    */

    std::cout << mwis[1]
              << mwis[2]
              << mwis[3]
              << mwis[4]
              << mwis[17]
              << mwis[117]
              << mwis[517]
              << mwis[997];
}
