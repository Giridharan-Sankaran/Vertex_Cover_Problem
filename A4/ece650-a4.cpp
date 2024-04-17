#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include<stdexcept>
#include<cmath>
#include<algorithm>
#include "ece650-a4.hpp"
#include<pthread>
#include<time>

pthread_t getinput, cnfsat, approxvc1, approxvc2;
pthread_mutex_t mutex;
std::vector<int> cnfsatres, approxvc1res, approxvc2res;
long long cnfsat_thread_time, approxvc1_thread_time, approxvc2_thread_time;


std::vector<int> VCusingCNFSAT(){
  int startvertex = 1; //Define start vertex as 1
  int endvertex = vertex; //Define end vertex as the input value of vertex
  int mid;
  std::vector<int> result; //Vector to store final result
  std::vector<int> vertexcover; //Vector to store the values from function.
  std::vector<int> temp = {-1};
  
  while(startvertex <= endvertex) //Binary search to find the minimum size of vertex cover.
  {
    mid = floor((startvertex+endvertex)/2);
    vertexcover = graph.computevertexcover(mid,vertex+1,edgevector);   //Function call to compute the vertex cover.
    bool checkifequal = std::equal(vertexcover.begin(), vertexcover.end(), temp.begin());
    
    if(not checkifequal)
    {
      endvertex = mid - 1;
      result.clear();
      result = vertexcover;
    }
    else
    {
      startvertex = mid + 1;
    }
    
      
  }
  
  std::sort(result.begin(),result.end());   //Sort the final result to print the final vertex cover.
  
  for(int cover:result)
  {
    std::cout<<cover<<" ";
  }
  std::cout<<"\n";
  return result;
}

std::vector<int> VCusingapproxVC1(){

  //get from PRANAV.
  
}

std::vector<int> VCusingapproxVC2(){

  //get from PRANAV.
  
}


void *VCusingCNFSAT_thread(void *arg){
  auto start_time = std::chrono::high_resolution_clock::now();
  pthread_mutex_lock(&mutex);
  cnfsatres = VCusingCNFSAT();
  auto elapsed_time = std::chrono::high_resolution_clock::now() - start_time;
  cnfsat_thread_time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count();
  pthread_mutex_unlock(&mutex);
  return 0;


}

void *VCusingapproxVC1_thread(void *arg){
  auto start_time = std::chrono::high_resolution_clock::now();
  pthread_mutex_lock(&mutex);
  approxvc1res = VCusingapproxVC1();
  auto elapsed_time = std::chrono::high_resolution_clock::now() - start_time;
  approxvc1_thread_time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count();
  pthread_mutex_unlock(&mutex);
  return 0;


}

void *VCusingapproxVC2_thread(void *arg){
  auto start_time = std::chrono::high_resolution_clock::now();
  pthread_mutex_lock(&mutex);
  approxvc2res = VCusingapproxVC2();
  auto elapsed_time = std::chrono::high_resolution_clock::now() - start_time;
  approxvc2_thread_time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed_time).count();
  pthread_mutex_unlock(&mutex);
  return 0;


}

void *inputvertexedge(void *arg) 
{
    int vertex = 0; //Define vertex as 0
    int c1=0;
    std::string edges; //String to get the edges
    std::string line; //String to get input line
    Graph graph; //Graph class definition
    std::vector<int> edgevector; //Vector to store values from edges

    while (!std::cin.eof()) {
        std::getline(std::cin, line);
        if(line.empty())
        {
            continue;
        }
        std::stringstream letter(line);
        char cmd;
        letter >> cmd;
        if (cmd == 'V') {
            letter >> vertex;
            if(vertex < 2)
            {
                throw std::runtime_error("Vertex is less than 2"); //To check for validation if vertex entered is less than 2
                break;
            }
            c1 = 0;
        }

        if ((cmd == 'E') && (c1==0) && (vertex > 1)){
            c1 = 1;
            edgevector.clear();
            letter >> edges;
            for (std::size_t i = 0; i < edges.size(); i++) {
                if (edges[i] == '{' || edges[i] == '}') {
                    edges.erase(i, 1);
                    i--;
                }
            } 

            std::stringstream edgelist1(edges);
            char len1, len2;
            int m, n;
            edgelist1 >> len1;
            while(len1 == '<')
            {
                edgelist1 >> m;
                edgevector.push_back(m);
                edgelist1 >> len1;
                edgelist1 >> n;
                edgevector.push_back(n);
                edgelist1 >> len2;
                edgelist1 >> len1;
                edgelist1 >> len1;
                if((m > vertex) || (n > vertex))
                {
                  throw std::runtime_error("Edge is greater than vertex");   //To check if given edge value is greater than the given vertex
                  break;
                }
                else
                {
                  continue;
                }
            }
            
            if(edgevector.size() == 0)
            {
              throw std::runtime_error("Edges are empty");
              break;
            }

            if(c1 == 1)
            {
              if(pthread_create(&cnfsat, NULL, &VCusingCNFSAT_thread, NULL) != 0) {
                throw std::runtime_error("Thread for CNF-SAT has been failed");   //To check if given edge value is greater than the given vertex
                break;

              }

              if(pthread_create(&approxvc1, NULL, &VCusingapproxVC1_thread, NULL) != 0) {
                throw std::runtime_error("Thread for Approx-VC1 has been failed");   //To check if given edge value is greater than the given vertex
                break;

              }

              if(pthread_create(&approxvc2, NULL, &VCusingapproxVC2_thread, NULL) != 0) {
                throw std::runtime_error("Thread for Approx-VC2 has been failed");   //To check if given edge value is greater than the given vertex
                break;

              }

              pthread_join(cnfsat, NULL);
              pthread_join(approxvc1, NULL);
              pthread_join(approxvc2, NULL);



            }
            
            
        }

    }
    return 0;
    
}



int main(){
  //int ret = 0;
  pthread_mutex_init(&mutex, NULL);
  try
  {
    if(pthread_create(&getinput, NULL, &inputvertexedge, NULL) != 0) {
      throw std::runtime_error("Thread for input has been failed");   //To check if given edge value is greater than the given vertex
      break;

    }

    pthread_join(getinput, NULL);

  }
  catch(const std::runtime_error& e)
  {
    std::cerr << "Error:" << e.what() << std::endl;
  }
}
