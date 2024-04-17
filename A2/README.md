## Shortest Path Finder
This program takes input until it sees EOF (End of File). One kind of input contributes towards the specification of an undirected graph, while another kind asks to print out a shortest path from one vertex to another in the current graph.

### Input Specification
#### Graph Specification:
Syntax: V <num_vertices>, E {<edge_1>, <edge_2>, ..., <edge_n>}
Description:
The specification of a set of vertices starts with V, followed by a space and an integer greater than one, all in a single line.
If the integer that follows the V is i, then the vertices are identified by 1, 2, ..., i.
The specification for a set of edges starts with E, followed by a space, and then the set of edges in a single line delimited by { and }.
The two vertices of an edge are delimited by < and > and separated by a comma.
The edges in the set are separated by a comma.
#### Shortest Path Query:
Syntax: s <vertex_id_1> <vertex_id_2>
Description:
Asks for a shortest path from the first vertex to the second.
The output comprises vertex IDs separated by -, with no whitespace within.

### Output
If a path does not exist between the vertices, an error is output starting with "Error:".

### Notes
The graph is specified by the specification of the set of vertices V followed by the set of edges E, in that order.
V and E always occur together.
There is no relationship between subsequent graph specifications; when a new V specification starts, all previous information can be forgotten.
After the specification of the graph, there can be zero or more shortest-path queries s.
For each s query, only one shortest path should be output; multiple shortest paths might exist, and an arbitrary choice can be made.