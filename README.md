# Pathfinding

**Initial implementation**

- Initially, we represented each vertex as simply a char, with no weighting. 
- We used an adjacency list representation of the graph, specifically using a hash map.

**Turning tha Graph into a Grid**
- The BFS implementation used an std::unordered_map to represent the adjacency list, and an std::unordered_set to represent the 'seen' vertices. An alternative would be to create
a struct for the vertices, and storing the information as attributes.

