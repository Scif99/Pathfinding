#include "implementation.cpp"

/*
- Single source shortest path (can find shortest path to any point from a given source)
- Requires non-negative costs at all vertices
- TO-DO: List why UCS is better than Dijkstra!
*/
//Technically UCS, since we don't initialise the queue as the full set of vertices... 


template<typename Location, typename Graph>
void Dijkstra(Graph G, Location source, Location goal,std::unordered_map<Location, Location>& came_from, std::unordered_map<Location, double>& cost_so_far) {

    std::unordered_set<Location> reached;

    //create priority queue
    auto cmp = [&cost_so_far] (Location a, Location b) {return cost_so_far[a] > cost_so_far[b];}; 
    std::priority_queue<Location,std::vector<Location>,decltype(cmp)> frontier(cmp);

    cost_so_far[source] = 0;
    frontier.push(source) ;
    came_from[source] = source;

    while(!frontier.empty()) {

        // Extract min
        Location current = frontier.top();
        frontier.pop();

        if (current == goal) break; //comment this out to search the whole graph 

        // Only process each node once.
        if(reached.find(current)!=reached.end()) continue; 
        reached.insert(current);

        for(Location next : G.neighbors(current)) {

            double new_cost = cost_so_far[current] + G.cost(current,next);

            if(cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {// in this implementation, check if a distance has been set
                cost_so_far[next] = new_cost;
                came_from[next] = current;
                frontier.push(next);
            }
        }
    }
}

/*
- Create a grid (see implementation for details) with a source and goal 
- Use Dijkstra to calculate shortest paths from the source
- Construct the path 
- Draw the grid (once with parent pointers, once with the shortest path, once with distances)
*/
int main() {
  GridWithWeights grid = make_diagram4();
  GridLocation start{1, 4}, goal{8, 3};

  std::unordered_map<GridLocation, GridLocation> came_from; // used to store parent vertices
  std::unordered_map<GridLocation, double> cost_so_far;

  Dijkstra(grid, start, goal, came_from, cost_so_far);
  //draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);
  std::cout << '\n';
  std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);
  //draw_grid(grid, nullptr, nullptr, &path, &start, &goal);
  std::cout << '\n';
  draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);
}