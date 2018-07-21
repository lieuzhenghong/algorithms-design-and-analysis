'''
Download the following text file (right click and select "Save As..."):
kargerMinCut.txt

The file contains the adjacency list representation of a simple undirected
graph. There are 200 vertices labeled 1 to 200. The first column in the file
represents the vertex label, and the particular row (other entries except the
first column) tells all the vertices that the vertex is adjacent to. So for
example, the 6th row looks like : "6 155 56 52 120 ......". This just means
that the vertex with label 6 is adjacent to (i.e., shares an edge with) the
vertices with labels 155,56,52,120,......,etc

Your task is to code up and run the randomized contraction algorithm for the
min cut problem and use it on the above graph to compute the min cut. (HINT:
Note that you'll have to figure out an implementation of edge contractions.
Initially, you might want to do this naively, creating a new graph from the old
every time there's an edge contraction. But you should also think about more
efficient implementations.)

(WARNING: As per the video lectures, please make
sure to run the algorithm many times with different random seeds, and remember
the smallest cut that you ever find.) Write your numeric answer in the space
provided. So e.g., if your answer is 5, just type 5 in the space provided.
*/
'''

from copy import deepcopy
from itertools import chain
import random
import math
import timeit

# String -> [[Int]]
# Reads a file FileName line by line, pushing each line into a list, then
# returns that list
def read_file(filename):
    lines = []
    with open(filename) as f:
        lines = f.readlines() 
        lines = [x.split() for x in lines]
    for (idx, line) in enumerate(lines):
        lines[idx] = list(map(int, lines[idx])) # applies int() to every item
                                                # in lines[idx]
    return lines

# [[Int]], [Int], Int, Int, -> [[Int]]
# Collapse two vertices into one. Removes self loops
# interp; v1 as the first vertice (row), v2 as the second vertice (entry in row)
def contract_edge(vertices, positions, v1, v2):
# IDEA: merge the two arrays together (in v1)
# Change all references to v2 to point to v1; this is a O(n) operation
# Remove self-loops, if any
    v1_row = vertices[positions.index(v1)]
    v2_row = vertices[positions.index(v2)]
    # We remove v2 and v1 because otherwise we will be counting the edge
    # between them, which doesn't exist anymore since we are collapsing the
    # edge
    v1_row.remove(v2)
    v2_row.remove(v1)
    v1_row = v1_row + v2_row[1:] # Merge step
    vertices.remove(v2_row)
    positions.remove(v2)
    # Make sure we mutate vertices before we enumerate it
    vertices[positions.index(v1)] = v1_row
    # Re-reference step
    for i, vertice_row in enumerate(vertices):
        for j, vertex in enumerate(vertice_row):
            if (vertex == v2):
                vertices[i][j] = v1
    # Remove all self-loops
    v1_row = [x for x in v1_row if (x != v1)]
    v1_row = [v1] + v1_row
    vertices[positions.index(v1)] = v1_row
    return(vertices)

def k_min_cut(vertices):
    positions = []
    for vertex in vertices:
        positions.append(vertex[0])
    while (len(vertices) > 2):
        # Select uniformly at random an edge:
        # Create a array of tuples of every single edge and select from there
        joined_array = []
        for sublist in vertices:
            label = sublist[0]
            for vertex in sublist[1:]:
                joined_array.append([label, vertex])
        v = random.choice(joined_array)
        v1 = v[0]
        v2 = v[1]
        vertices = contract_edge(vertices, positions, v1, v2)
    # Once the while loop has completed, we have the two vertices; those
    # correspond to the minimum cut according to the algorithm
    # The number of parallel edges between the two vertices (i.e. the length of
    # either A or B vertice) is the result we want
    return(len(vertices[0])-1) #-1 because the first element is the label!
    
# Stopping condition: when there are only two vertices left; that is, when the
# length of vertices becomes 2
def main():
    vx = read_file("kargerMinCut.txt")
    n_squared = len(vx);
    k = math.log(0.01)/math.log((n_squared-1)/n_squared)
    min_cut_so_far = math.inf
    start = timeit.default_timer()
    print("Running {} trials...".format(k))
    for i in range(math.floor(k)):
        # As the vertices array will be mutated by the k_min_cut function on
        # every iteration, we shouldn't mutate the actual array. hence we make
        # a (deep) copy of it
        vertices = deepcopy(vx)
        min_cut = k_min_cut(vertices)
        print("Completed trial {} of {}. Cut was {}, best so far {}".format(i+1,
        int(k), min_cut, min_cut_so_far))
        if (min_cut < min_cut_so_far):
            min_cut_so_far = min_cut
    print("Completed all trials. Min cut is: {}".format(min_cut_so_far))
    stop = timeit.default_timer()
    print ('Time taken: {0} seconds'.format(stop-start))
    return(min_cut_so_far)

print(main())
