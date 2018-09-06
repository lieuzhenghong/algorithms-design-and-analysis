'''
A naive implementation of Dijkstra's algorithm

Dijkstra's algorithm takes a start node S and an end node E
Runs in O(nm) time where n is the number of vertices and m is the number of
edges

This algorithm will return the shortest-path distance from S to E

My assignment tells me to do the following:

If there is no path between a vertex v and vertex 1, we'll define the
shortest-path distance between 1 and v to be 1000000.  You should report the
shortest-path distances to the following ten vertices, in
order: 7,37,59,82,99,115,133,165,188,197. Enter the shortest-path distances
using the fields below for each of the vertices.

Dijkstra's algorithm works as follows:
- There is a discovered region X and a frontier region V-X
- For every edge from X to V-X, (from vertice v to w) we calculate the
  Dijkstra's greedy score: the cost to get from S -> v plus the cost of the
  edge vw (store greedy score in dist)
- Take the vertice with the lowest greedy score and add it to the
  discovered region X
'''

import argparse

#vertices = [[]] * 201
vertices = [[]]
dist = [1000000]
discovered_vertices = []
undiscovered_vertices = []
edges = []
num_vertices = 0;

def read_file(file_name):
    global num_vertices
    with open(file_name, 'r') as f:
        for index, line in enumerate(f):
            num_vertices += 1
            edges = line.split("\t")
            vertices.append([])
            undiscovered_vertices.append(index+1) #vertices are 1-indexed
            dist.append(1000000)
            for edge in edges[1:]:
                if (edge.strip() is not ''):
                    vertices[index+1].append([int(y) for y in edge.strip().split(",")])
            #print(index+1, ":", vertices[index+1])

    for (source_vertex, edges) in enumerate(vertices):
        for edge in edges:
            print(edge)
            if (edge[0] == source_vertex):
                pass
            # edge[0] => source vertex, edge[1] is distance,
            # index => destination vertex
            else:
                vertices[edge[0]].append([source_vertex, edge[1]]) 

    dist[args.start] = 0 # dist from source vertex to source vertex is always 0
    #print(dist)
    discovered_vertices.append(int(args.start))
    for index, vertex in enumerate(vertices):
        print(index, ':', vertex)
    #print(dist)
#print(len(dist))


def dijkstra():
    '''
    Vertices are 1-indexed

    dist is an array of every single vertex from 0 to 201 (there are
    200 vertices) and looks like this:
    [1000000, 1000000, ..... 1000000] <- 201 entries

    undiscovered_vertices is just an array that starts off with all the
    vertices {1, 200} in it

    vertices[n] gives the edges of the nth vertex and looks like this:

    [ [8, 392], [80, 4930], [157, 2246] .... ] where the first value is the
    destination vertex and the second value is the distance
    '''
    num_undiscovered = len(undiscovered_vertices)
    while (num_undiscovered > 0):
        # vertices are 1-indexed, so 0 is a placeholder vertex
        shortest_vertex = 0
        # get the shortest length in u_d
        for v in undiscovered_vertices:
            if (dist[v] < dist[shortest_vertex]):
                shortest_vertex = v

        # remove shortest_vertex from undiscovered
        idx = undiscovered_vertices.index(shortest_vertex)
        undiscovered_vertices.pop(idx)
        num_undiscovered -= 1

        # iterate over each of shortest_vertex's neighbours
        for [new_vert, new_dist] in vertices[shortest_vertex]:
            new_dist = new_dist + dist[shortest_vertex]
            if (new_dist < dist[new_vert]):
                dist[new_vert] = new_dist

        out = dist
        #print([out[7], out[37], out[59], out[82], out[99], out[115],
        #       out[133], out[165], out[188], out[197]])
    return(dist)

parser = argparse.ArgumentParser(description="Computes Dijkstra's algorithm \
given a filename, start node and end node")
parser.add_argument('filename', help='name of the adjacency list representation of the graph')
parser.add_argument('start', type=int, help='label of the start node')
args = parser.parse_args()

if __name__ == "__main__":
    read_file(args.filename)

    #out = main()
    out = dijkstra()
    print([out[7], out[37], out[59], out[82], out[99], out[115],
           out[133], out[165], out[188], out[197]])
    #print(out)
