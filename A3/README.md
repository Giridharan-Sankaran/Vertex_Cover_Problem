## IPC-based Graph Generator and Shortest Path Finder
This project involves generating random street specifications as input for a Python script, linking the output of the Python script to the input of a C++ program, and then outputting the input graph of the C++ program along with providing shortest path queries.

### Random Input Generator (rgen)
The random input generator, rgen, generates random street specifications for the Python script. It takes the following optional command-line arguments:

-s k: Specifies the upper bound for the number of streets (default: 10).
-n k: Specifies the upper bound for the number of line-segments in each street (default: 5).
-l k: Specifies the upper bound for the wait time in seconds before generating the next input (default: 5).
-c k: Specifies the range for (x, y) coordinates (default: 20).
The generator ensures that the generated input does not have errors, such as overlapping line segments or zero-length line segments. It limits the number of attempts to generate valid input to prevent infinite loops.

### Python Script
The Python script takes input from the random input generator and produces output in the format expected by the C++ program. It maps each vertex to an index in [1, n], where n is the number of vertices, and renames the edges accordingly. The output of the Python script is the specification of the graph in the format required by the C++ program. Error output is directed to stderr.

### C++ Program
The C++ program reads the input graph produced by the Python script before accepting a shortest path query. It outputs the input graph on standard output before processing any queries. Shortest path queries (s) can be issued repeatedly, and the program outputs a shortest path between the specified vertices.

### Driver Program
The driver program uses Inter-Process Communication (IPC) to link the output of the random input generator to the input of the Python script, and the output of the Python script to the input of the C++ program. It takes input from stdin and outputs to stdout. Errors are output to stderr. All processes terminate gracefully upon EOF at stdin.