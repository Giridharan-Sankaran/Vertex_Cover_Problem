#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <vector>
#include <sys/types.h>
#include <signal.h>

//This routine is developed as a driver program to perform random generation of street coordinates, compute vertices and edges and find the shortest path between them using fork and pipes.  

int main(int argc, char **argv) {
  std::string g;
  int ch;
  int status1;
  opterr = 0;
  int sdef = 10, ndef = 5, ldef = 5, cdef = 20; //Default values if no values are defined in command line
  while((ch = getopt(argc, argv, "s:n:l:c:")) != -1)
    switch(ch) {
      case 's':
        g = optarg;
        sdef = atoi(g.c_str());
        if (sdef < 2)
        {
          std::cerr<<"Error : Number of streets should be greater than 2"<<std::endl;
          exit(0);
        }
        break;
      case 'n':
        g = optarg;
        ndef = atoi(g.c_str());
        if (ndef < 1)
        {
          std::cerr<<"Error: Number of line segments should be greater than 1"<<std::endl;
          exit(0);
        }
        break;
      case 'l':
        g = optarg;
        ldef = atoi(g.c_str());
        if (ldef < 5)
        {
          std::cerr<<"Error: Waiting of random number should be greater than 5 secs"<<std::endl;
          exit(0);
        }
        break;
      case 'c':
        g = optarg;
        cdef = atoi(g.c_str());
        if (cdef < 1)
        {
          std::cerr<<"Error: Coordinates range is less than 1"<<std::endl;
          exit(0);
        }
        break;
      case '?':
        if(optopt == 's' || optopt == 'n' || optopt == 'l' || optopt == 'c')
          std::cerr<<"Error: Option requires an argument"<<std::endl;
        else
          std::cerr<<"Error: Unknown option"<<std::endl;
        return 1;
      default:
        return 0;
      }
  char* rgarg[10];                                        //character array to invoke random generator routine.
  rgarg[0] = (char*)"./rgen";
  rgarg[1] = (char*)"-s";
  rgarg[2] = (char*)std::to_string(sdef).c_str();
  rgarg[3] = (char*)"-n";
  rgarg[4] = (char*)std::to_string(ndef).c_str();
  rgarg[5] = (char*)"-l";
  rgarg[6] = (char*)std::to_string(ldef).c_str();
  rgarg[7] = (char*)"-c";
  rgarg[8] = (char*)std::to_string(cdef).c_str();
  rgarg[9] = nullptr;
  
  char* py[3];                                            //character array to invoke python file to find vertex and edges.
  py[0] = (char*)"/usr/bin/python3";
  py[1] = (char*)"ece650-a1.py";
  py[2] = nullptr;
  
  char* cpp[2];                                          //character array to invoke cpp file to compute shortest path.
  cpp[0] = (char*) "ece650-a2.cpp";
  cpp[1] = (char*) nullptr;
  
  
  int RGtoP[2];
  int PtoCPP[2];
  std::vector<pid_t> processes;
  
  pipe(RGtoP);                                            //Definition of pipes to connect the different processes
  pipe(PtoCPP);
  

  
  
  pid_t pid1 = fork();                                    //Fork to run random generator file.
  
  if(pid1 == 0)
  {
    close(RGtoP[0]);
    dup2(RGtoP[1], 1);
    execv("./rgen",rgarg);
    
  }
  else if(pid1 < 0){
    std::cerr<<"Error: Issue with starting a process1"<<std::endl;
    return 1;
  }
  
  processes.push_back(pid1);
  
  
  pid_t pid2 = fork();                                    //Fork to run python file
  
  
  if(pid2 == 0)
  {
    close(RGtoP[1]);
    dup2(RGtoP[0], 0);
    close(PtoCPP[0]);
    dup2(PtoCPP[1], 1);
    execv("/usr/bin/python3",py);

   }
   else if(pid2 < 0){
    std::cerr<<"Error: Issue with starting a process2"<<std::endl;
    return 1;
  }
  
  processes.push_back(pid2);
  
  pid_t pid3 = fork();                                    //Fork to run cpp file for shortest path.
  
  
  if(pid3 == 0)
  {
    close(PtoCPP[1]);
    dup2(PtoCPP[0], 0);
    execv("./ece650-a2",cpp);

   }
   else if(pid3 < 0){
    std::cerr<<"Error: Issue with starting a process3"<<std::endl;
    return 1;
  }
  
  processes.push_back(pid3);                              
  dup2(PtoCPP[1],1);                                       //Parent process         
  
  
  while((waitpid(pid1, &status1, WNOHANG)!= pid1) && !std::cin.eof())              //Loop to get input for shortest path
  {
    std::string line;
    std::getline(std::cin, line);
    std::cout<<line<<std::endl;
  }
  close(PtoCPP[0]);
  close(PtoCPP[1]);
  close(RGtoP[0]);
  close(RGtoP[1]);
  
  for(auto terminate : processes)                                                  //Loop to kill the child processes
  {
    int status;
    kill(terminate, SIGTERM);
    waitpid(terminate,&status,0);
  }
  
  return 0;
}
