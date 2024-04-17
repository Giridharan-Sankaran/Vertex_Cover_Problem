#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<stdexcept>
#include <signal.h>
#include <unistd.h>

#include "ece650-a2.hpp"

int main(int argc, char **argv) {
    int vertex = 0;
    int c1=0;
    int d = 0;
    int check = 0;
    std::string edges;
    int startnode, endnode;
    std::string line;
    Graph graph;

    std::vector<std::vector<int>> adjlist; //adjacency list to store the edges

    while (!std::cin.eof()) {
        std::getline(std::cin, line);
        if(line.empty())
        {
            continue;
        }
        std::stringstream letter(line);
        char cmd;
        letter >> cmd;

        try
        {

            if (cmd == 'V') {
                std::cout<<line<<std::endl;                            //Printing vertex generated from python
                letter >> vertex;
                if(vertex < 2)
                {
                    throw std::runtime_error("Vertex is less than 2"); //To check for validation if vertex entered is less than 2
                    break;
                }
                c1 = 0;
            }

            if ((cmd == 'E') && (c1==0) && (vertex > 1)){
                d = 0;
                c1 = 1;
                std::cout<<line<<std::endl;                            //Printing edges generated from python                            
                letter >> edges;
                for (std::size_t i = 0; i < edges.size(); i++) {
                    if (edges[i] == '{' || edges[i] == '}') {
                        edges.erase(i, 1);
                        i--;
                    }
                } 

                std::stringstream edgelist(edges);
                std::stringstream edgelist1(edges);
                char len1, len2;
                int m, n;
                int count = 0;
                edgelist1 >> len1;
                while(len1 == '<')
                {
                    edgelist1 >> m;
                    edgelist1 >> len1;
                    edgelist1 >> n;
                    edgelist1 >> len2;
                    count = count + 1;
                    edgelist1 >> len1;
                    edgelist1 >> len1;
                }
                adjlist.resize(vertex+count + 1);
                adjlist.clear();

                check = graph.splitedges(edgelist, vertex, adjlist, d);
                if (check == 1){
                    throw std::runtime_error("Edge is greater than vertex"); //To check for validation if given edges is greater than vertex
                }
            }


            if (cmd == 's') {
                c1 = 0;
                if (check == 1){
                    throw std::runtime_error("Given edges are wrong");
                    break;
                }
                letter >> startnode;
                letter >> endnode;
                if(edges.empty())
                {
                    throw std::runtime_error("Edges should be given before entering shortest path"); //To check for validation if edges are defined before entering shortest path.
                    break;

                }
                if((startnode < 1) || (endnode < 1) || (startnode >vertex)|| (endnode > vertex))
                {
                    throw std::runtime_error("Shortest path not within boundaries"); //To check for validation if edges are defined before entering shortest path.
                    break;
                }
                std::vector<int> finalout = graph.bfsshortpath(adjlist, startnode, endnode);
                for (size_t i = 0; i < finalout.size(); ++i) {
                    std::cout << finalout[i];
                    if (i != finalout.size() - 1) {
                        std::cout << "-";
                    }
                }
                std::cout << std::endl;
            }
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << "Error:" << e.what() << std::endl;

        }
        
    }
    return 0;
}
