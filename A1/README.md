## Street Graph Construction
This project involves constructing a particular kind of undirected graph based on a series of commands that describe streets. The coding is done in Python.

### Input Commands
The input comprises lines, each specifying a command. There are 4 kinds of commands:

### Add a Street:
Syntax: add "Street Name" (x1, y1) (x2, y2) . . . (xn, yn)
Description: Adds a street defined by a series of GPS coordinates forming a polyline segment.

### Modify a Street:
Syntax: mod "Street Name" (x1, y1) (x2, y2) . . . (xn, yn)
Description: Modifies the specification of a previously added street.

### Remove a Street:
Syntax: rm "Street Name"
Description: Removes a street from the graph.

### Generate a Graph:
Syntax: graph
Description: Outputs the corresponding graph based on the input streets.

### Graph Construction:
The output of the graph is structured in such a way that:
Each intersection corresponds to a vertex.
The end-point of a line segment of a street that intersects with another street also corresponds to a vertex.

### Vertex Identification
The identity of a vertex can be any string of letters or integers (but no special characters). For example, v1xyz is acceptable as the identity of a vertex, but not v1 !!#xyz.

### Edge Construction
An edge exists between two vertices if:
At least one of them is an intersection.
Both lie on the same street.
One is reachable from the other without traversing another vertex.

### Example
For example, the edge ⟨1, 3⟩ connects the end-point of a line segment.