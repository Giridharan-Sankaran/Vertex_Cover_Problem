//This cpp file holds the definitions for each functions that are declared in the hpp file.

#include "ece650-a4.hpp"
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include<stdexcept>
#include <memory>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <iostream>


std::vector<int> Graph::computevertexcover(int mid, int vertex, std::vector<int> edgevector)
{
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());  //Definition of Minisat solver
  std::vector<int> E1;
  std::vector<int> E2;
  
  for(size_t y=0; y < edgevector.size(); ++y)   //Storing of edges in two different vectors to use it for the fourth reduction clause.
  {
    if(y%2 == 0)
    {
      E1.push_back(edgevector[y]);
    }
    else
    {
      E2.push_back(edgevector[y]);
    }
  }
  
  std::vector<std::vector<Minisat::Lit>> array(vertex);   //Define a 2-D array to store the literals
  
  for(int n=0; n < vertex; ++n)
  {
    for(int k=0; k < mid; ++k)
    {
      Minisat::Lit literal;
      literal = Minisat::mkLit(solver->newVar());
      array[n].push_back(literal);
    }
  }
  
  //Condition for clause-1 : At least one vertex is the ith vertex in the vertex cover.
  
  for(int u=0; u < mid; ++u)
  {
    Minisat::vec<Minisat::Lit> lits;
    for(int v=0; v < vertex; ++v)
    {
      lits.push(array[v][u]);
    }
    solver->addClause(lits);
    lits.clear();
  }
  
  
  
  
  //Condition for clause-2 : No one vertex can appear twice in a vertex cover.
  for(int e =0; e < vertex; ++e)
  {
    for(int f=0; f < mid-1; ++f)
      {
        for(int g=f+1; g < mid; ++g)
        {
          solver->addClause(~array[e][f], ~array[e][g]);
        }
      }
  }
  
  
  
  //Condition for clause-3 : No more than one vertex appears in the mth position of the vertex cover.
  for(int h=0; h < mid; ++h)
  {
    for(int p=0; p < vertex-1; ++p)
    {
      for(int q=p+1; q < vertex; ++q)
      {
        solver->addClause(~array[p][h], ~array[q][h]);
      }
    }
  }
  
  //Condition for clause-4 : Every edge is incident to at least one vertex in the vertex cover.
  
  for(size_t b=0; b < E1.size(); ++b)
  {
    Minisat::vec<Minisat::Lit> lits;
    for(int c=0; c < mid; ++c)
    {
      lits.push(array[E1[b]][c]);
      lits.push(array[E2[b]][c]);
      
    }
    solver->addClause(lits);
    lits.clear();
  }
  
  bool res = solver->solve();
  
  if(res)
  {
    std::vector<int> res1;
    
    for(int w=0; w < vertex; ++w)
    {
      for(int x=0; x < mid; ++x)
      {
        if(Minisat::toInt(solver->modelValue(array[w][x])) == 0)
        {
          res1.push_back(w);
        }
      }
    }
    return res1;
  }
  else
  {
    return {-1};
  }
  solver.reset (new Minisat::Solver());   //De-allocates existing solver and allocates new one.
  return {0};

}
  
  
  
  
    


