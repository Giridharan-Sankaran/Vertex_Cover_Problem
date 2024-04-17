#include <iostream>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <set>
#include <sstream>
#include <utility>

//This routine is developed to generate streetnames and coordinates for streets randomly. The randomly generated streets and coordinates are given as inputs to the Python file for computing vertices and edges.

//Function to check if there any line sgement is overlapping
bool checkslope(std::vector<std::string> coor1, std::vector<int> set2, std::vector<int> sete)  
{
    std::vector<std::string> coor2;
    coor2 = coor1;
    std::vector<int> set3;
    std::vector<int> set4;
    set3 = set2;
    set4 = sete;
    std::vector<std::pair<int, int>> c;
    int count = 0;
    for (const std::string& coordinate : coor2) {
      std::istringstream convert(coordinate);
      char var1;
      int x1, x2;

      while (convert >> var1) {
          if (var1 == '(') {
            convert >> x1;
            convert >> var1;
            convert >> x2;
            convert >> var1;
            c.push_back(std::make_pair(x1,x2));
          }
      }
    }
    
    for(size_t i=0;i < c.size()-1; i++)
    {
      if(((c[i].first == c[i+1].first) && (set3[0] == set4[0]) && (((c[i].second <= set3[1]) && (set3[1]<= c[i+1].second)) && ((c[i].second <= set3[1]) && (set3[1] <= c[i+1].second)))) || ((c[i].first == c[i+1].first) && (set3[0] == set4[0]) && (((c[i].second >= set3[1]) && (set3[1] >= c[i+1].second)) && ((c[i].second >= set3[1]) &&  (set3[1] >= c[i+1].second)))) || ((c[i].second == c[i+1].second) && (set3[1] == set4[1]) && (((c[i].first <= set3[0]) && (set3[0] <= c[i+1].first)) && ((c[i].first <= set4[0]) && (set4[0] <= c[i+1].first)))) || ((c[i].second == c[i+1].second) && (set3[1] == set4[1]) && (((c[i].first >= set3[0]) && (set3[0] >= c[i+1].first)) && ((c[i].first >= set4[0]) && (set4[0] >= c[i+1].first)))))
      {
        count = 1;
      }
    }
    if(count !=1)
    {
      return false;
    }
    else
    {
      return true;
    }
}

  

//Function to create coordinates randomly
std::vector<std::string> create_coordinates(std::vector<std::string> streetname,int ndef, int cdef)  
{
  std::vector<std::string> street1;
  std::vector<std::string> coor;
  int ndef1, cdef1, ndef2;
  street1 = streetname;
  ndef1 = ndef;
  cdef1 = cdef;
  int x,y;
  int prevx,prevy;
  int limit = 0, c = 0;
  int minval = -cdef1;
  int maxval = cdef1;
  std::vector<int> set1;
  std::vector<int> setd;
  std::ifstream urandom("/dev/urandom", std::ios::binary);

  if(!urandom) {
    std::cerr <<"Failed to open /dev/urandom" <<std::endl;
    return coor;
  }
  for(size_t l = 1; l <= street1.size(); ++l)
  {
    limit = 0;
    set1.clear();
    int ran;
    urandom.read(reinterpret_cast<char*>(&ran), sizeof(ran));
    //urandom.close();
    ndef2 = 1 + (std::abs(ran) % (ndef1 - 1 + 1));
    //std::cout<<ndef1<<std::endl;
    //ndef1 = 1 + (rand() % ndef1);
    c = 0;
    std::string lineSegment = "(";
    for(int m = 0; m <= ndef2; ++m){
      bool checkunique = false;
      bool checkoverlap = false;
      while((!checkunique) && (limit <= 25))
      {
        urandom.read(reinterpret_cast<char*>(&x), sizeof(x));
        urandom.read(reinterpret_cast<char*>(&y), sizeof(y));
        x = minval + (std::abs(x) % (maxval - minval + 1));
        y = minval + (std::abs(y) % (maxval - minval + 1));
        if(coor.size() > 0)
        {
          if(set1.size() == 0)
          {
            set1.push_back(x);
            set1.push_back(y);
          }
          else
          {
            setd.push_back(x);
            setd.push_back(y);
            
          }
          size_t setlen = set1.size();
          size_t setlen1 = setd.size();
          if((setlen == 2) && (setlen1 == 2))
          {
            checkoverlap = checkslope(coor,set1,setd);
            if(checkoverlap)
            {
              limit = limit + 1;
              setd.clear();
            }
            else
            {
              set1 = setd;
              setd.clear();
            }
          }
        }
        int distance = std::abs(x-prevx) + std::abs(y-prevy);
        if(distance !=0) {
          std::string newsegment = std::to_string(x) + "," + std::to_string(y);
          if(lineSegment.find(newsegment) == std::string::npos) {
            bool segmentunique = true;
            for(size_t k =0; k < coor.size(); ++k) {
              if(coor[k].find(newsegment) != std::string::npos) {
                segmentunique = false;
                limit = limit + 1;
                break;
              }
            }
            if (segmentunique && (!checkoverlap)) {
              lineSegment += newsegment;
              prevx = x;
              prevy = y;
              checkunique = true;
            }
          }
        }
      }
      if(limit > 25)
      {
        std::cerr<<"Error: failed to generate valid input for 25 simultaneous attempts"<<std::endl;
        c = c + 1;
        exit(1);
        break;
      }
      else if (m < ndef2) {
        lineSegment += ") (";
      }
    }
    if (c > 0)
    {
      coor.clear();
      break;
    }
    else
    {
      lineSegment += ")";
      coor.push_back(lineSegment);
    }
  }
  urandom.close();
  return coor;
}
  


//Function to create streets randomly
std::vector<std::string> create_street(int sdef) 
{                          
  std::vector<std::string> streets;
  int sdef1 = sdef;

  std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
  if (!urandom) {
    std::cerr << "Failed to open /dev/urandom" << std::endl;
    return streets;
  }

  for (int i = 1; i <= sdef1; ++i) {
    std::string gtch;
    bool checkstreet = false;
    while (!checkstreet) {
      int length;
      urandom.read(reinterpret_cast<char*>(&length), sizeof(length));
      length = std::abs(length) % 50 + 1;

      gtch.clear();
      for (int j = 0; j < length; ++j) {
        char randomChar;
        urandom.read(&randomChar, sizeof(randomChar));
        if(randomChar != '\0' && (isalpha(randomChar) || isdigit(randomChar))) gtch += randomChar;
      }

      if (!gtch.empty()) {
        bool streetunique = true;
        for (const std::string& existingStreet : streets) {
          if (existingStreet == gtch) {
            streetunique = false;
            break;
          }
        }
        if (streetunique) {
          gtch = gtch + std::to_string(i);
          streets.push_back(gtch);
          checkstreet = true;
        }
      }
    }
  }

  urandom.close();
  return streets;
}


//Function to generate random ranges for input values
int finalgenerator(char cmd,int range){                                            
  std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
  if (!urandom){
    std::cerr<<"Failed to open dev/urandom"<<std::endl;
    return 1;
  }
  
  int randval,minval,maxval;
  urandom.read(reinterpret_cast<char*>(&randval), sizeof(randval));
  urandom.close();
  
  if(cmd == 's')
  {
    minval = 2;
    maxval = range;
  }
  
  if(cmd == 'n')
  {
    minval = 1;
    maxval = range;
  }
  
  if(cmd == 'l')
  {
    minval = 5;
    maxval = range;
  }
  
  return minval + (std::abs(randval) % (maxval - minval + 1));
}
  
  


int main(int argc, char **argv) {
  srand(time(0));
  std::string g; 
  int ch;
  int check = 1;
  opterr = 0;
  int sdef = 10, ndef = 5, ldef = 5, cdef = 20;                  //Default values for rgen if nothing is specified in command line
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
      
  while(check)
  {
    std::vector<std::string> streetname;
    std::vector<std::string> coordinates;
    std::vector<std::string> r;
    int sfinal,nfinal,lfinal;
    sfinal = finalgenerator('s', sdef);                                  //Randomly generating values for 's'
    nfinal = finalgenerator('n', ndef);                                  //Randomly generating values for 'n'
    lfinal = finalgenerator('l', ldef);                                  //Randomly generating values for 'l'
    streetname = create_street(sfinal);
    coordinates = create_coordinates(streetname,nfinal,cdef);
    if(coordinates.size() == 0)
    {
      check=0;
      break;
    }
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    for(size_t q = 0; q < streetname.size(); ++q)
    {
      std::cout<<"add ";
      r.push_back("\"" + streetname[q] + "\"" + " " + coordinates[q]);
      std::cout<<r[q]<<std::endl;
    }
    std::cout<<"gg"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(lfinal));
    
    for (size_t f = 0; f<streetname.size(); ++f)
    {
      std::cout<<"rm "<<"\""<<streetname[f]<<"\""<<std::endl;
    }
    //std::this_thread::sleep_for(std::chrono::seconds(lfinal));
    
  }
}




