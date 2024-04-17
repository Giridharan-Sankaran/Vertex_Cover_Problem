//This hpp file is created to hold the function declarations required for finding the shortest path of a undirected graph.

#include<string>
#include<vector>

class Graph
{
    public:

    void addedges(std::vector<std::vector<int>> &adjlist, int u, int v); //This function is used to add edges into an adjacency list.

    std::vector<int> bfsshortpath(std::vector<std::vector<int>> &adjlist, int startnode, int endnode); //This function is used to find and print the shortest path of the undirected graph.

    int splitedges(std::stringstream& edgelist, int vertex, std::vector<std::vector<int>> &adjlist, int& d); // This function is used to split the edges from the given input into the form of (u,v).


};