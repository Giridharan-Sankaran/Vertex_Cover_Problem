
## Multithreaded Minimum Vertex Cover Solver
This assignment involves augmenting the code from Assignment 4 to solve the minimum vertex cover problem using multithreading and implementing additional approaches for solving MIN-VERTEX-COVER.

### Multithreading
The code will be made multithreaded with at least 4 threads:
One thread for I/O.
One thread for each of the different approaches to solve the minimum vertex cover problem.

### Additional Approaches
In addition to the REDUCTION-TO-CNF-SAT approach from Assignment 4 (referred to as CNF-SAT-VC), the following two additional approaches will be implemented:

### APPROX-VC-1:
Algorithm: Pick a vertex of highest degree (most incident edges), add it to the vertex cover, and remove all incident edges. Repeat until no edges remain.
### APPROX-VC-2:
Algorithm: Pick an edge ⟨u, v⟩, add both u and v to the vertex cover, and remove all edges incident to u and v. Repeat until no edges remain.

### Efficiency Analysis
### Running Time Measurement:
Use pthread_getcpuclockid() to measure the running time.
Generate graphs for various values of |V| (number of vertices) using the graphGen program, in increments of 5 (from 5 to 50 vertices).
Measure the running time for at least 10 runs of each graph.
Compute the mean and standard deviation across those runs for each value of |V|.

### Approximation Ratio Measurement:
Compare the size of the computed vertex cover to the size of an optimal vertex cover produced by CNF-SAT-VC.
Generate at least 10 graphs for each value of |V|.
Measure the approximation ratio multiple times for each graph if there is any random component.
Compute the mean and standard deviation across those runs for each value of |V|.

### Handling Large Instances:
Use a timeout to avoid waiting indefinitely for the result of CNF-SAT-VC on large instances.
Produce "CNF-SAT-VC: timeout" in the output for such instances.

### Scaling CNF-SAT-VC
CNF-SAT-VC can be scaled significantly by improving the encoding.