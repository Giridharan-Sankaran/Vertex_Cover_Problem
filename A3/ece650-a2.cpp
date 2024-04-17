//This cpp file holds the definitions for each functions that are declared in the hpp file.

#include "ece650-a2.hpp"
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include<stdexcept>



void Graph::addedges(std::vector<std::vector<int>> &adjlist, int u, int v) 
    {
        adjlist[u].push_back(v); //appending edges into adjacency list
        adjlist[v].push_back(u);
    }

std::vector<int> Graph::bfsshortpath(std::vector<std::vector<int>> &adjlist, int startnode, int endnode) //Function to find shortpath
{
    std::unordered_map<int, int> parentnode;
    std::unordered_map<int, bool> checkvisit;
    std::queue<int> q;
    std::vector<int> output;
    int start = startnode;
    int end = endnode;
    int c = 0;

    q.push(start);
    checkvisit[start] = true;
    parentnode[start] = -1;

    while (!q.empty()) {
        int frontelem = q.front();
        q.pop();

        if (frontelem == end) {
            c = 1;
            break;
        }
        for (auto j : adjlist[frontelem]) {
            if (!checkvisit[j]) {
                q.push(j);
                checkvisit[j] = true;
                parentnode[j] = frontelem;
            }
        }
    }

    if (!c) {
        throw std::runtime_error("Path doesn't exist between the given nodes");
    } else {
        while (end != start) {
            output.push_back(end);
            end = parentnode[end];
        }
        output.push_back(start);
        std::reverse(output.begin(), output.end());
    }
    return output;
}

int Graph::splitedges(std::stringstream& edgelist, int vertex, std::vector<std::vector<int>> &adjlist, int& d) //Function to check if edges are given correctly before appending to list.
{
    char len;
    int u,v;
    while ((edgelist >> len) && (d == 0)) {

        if (len == '<') {
            edgelist >> u;
            edgelist >> len;
            edgelist >> v;
            edgelist >> len;
            if ((u > vertex) || (v > vertex) || (u < 1) || (v < 1)) {
                d = 1;
                return 1;
            } else {
                addedges(adjlist, u, v);
            }
        }
    }
    return 0;

}