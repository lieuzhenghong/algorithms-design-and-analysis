#include <iostream>
#include <fstream>
#include <vector>

/*
 *Download the following text file (right click and select "Save As..."): kargerMinCut.txt

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

std::string readfile(filename) {

}

int main() {
  std::ifstream infile("kargerMinCut.txt");
  std::vector <std::vector<int>> vertices;
  std::string line;

  while (std::getline(infile, line)) {
    std::cout << line << std:: endl;
    vertices.push_back(line);
    std::cout << line << std::endl;
  }
}

// Vector<[int]>, Int, Int -> Vector<[int]>
// Given any two vertices (i.e. an edge), collapses the two vertices.
// Removes self-loops.
std::vector<std::vector<int>> edge_contract(std::vector<std::vector<int>> vertices, int vertex1, int
vertex2) {
  std::cout << vertices[0][0] << std::endl;
}

/* How do you pick an edge randomly and uniformly? If you simply pick a index
 * in the vertices array, that's not going to be fair: some vertices have more
 * edges than others.
 */


