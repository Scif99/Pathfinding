# Pathfinding

#Notes
- The BFS implementation used an std::unordered_map to represent the adjacency list, and an std::unordered_set to represent the 'seen' vertices. An alternative would be to create
a struct for the vertices, and storing the information as attributes.

**Hashing with user-defined types**
- You can represent a graph as a grid by defining each point as having an x and a y value. However since this is a user-defined type, you cannot use the built-in hash functions as they are only specialised for primitive types.
To 
