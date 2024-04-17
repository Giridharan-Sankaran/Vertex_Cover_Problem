## Minimal Vertex Cover Solver using SAT
This assignment involves augmenting the code from Assignment 2 to solve the minimal Vertex Cover problem for the input graph using a SAT solver, specifically MiniSat.

### SAT Solver
We will be using MiniSat SAT solver for this assignment.

### Incorporating SAT
#### Reduction to CNF-SAT:
Create a polynomial reduction of the decision version of VERTEX COVER to CNF-SAT. You are allowed to use your own reduction as long as it is sound and polynomial-time.
#### Implementation:
Implement the reduction and use MiniSat as a library to solve the minimum VERTEX COVER problem for the input graphs.
### Usage
As soon as an input graph is received via the V and E specifications, the program computes a minimum-sized Vertex Cover and immediately outputs it.
The output consists of a sequence of vertices in increasing order, separated by one space each.
Sorting can be done using qsort(3) or std::sort.
### Notes
Ensure that the reduction is sound and polynomial-time.
The output should be produced promptly upon receiving the input graph.