#include "implementation.cpp"

/*
A* (A-star) 
- Single source, single goal
- A* is similar to UCS, except for the notion of distance
- It uses a heuristic, which biases the exploration towards the goal
- 

*/




template<typename Graph, typename Location>
void a_star_search(Graph G, Location source, Location goal, std::unordered_map<Location,Location>& came_from, std::unordered_map<Location, double>& cost_so_far){

    std::unordered_set<Location> reached;

    std::unordered_map<Location, double> priority;
    priority[source] = heuristic(source,goal);

    //now the priority queue maintains order over the sum of the cost_so_far and the heuristic
    auto cmp = [&priority] (Location a, Location b) {return priority[a] > priority[b];};
    std::priority_queue<Location,std::vector<Location>,decltype(cmp)> frontier(cmp);
    frontier.push(source);

    cost_so_far[source] = 0;
    came_from[source] = source;

    while(!frontier.empty()) {

        // Extract min
        Location current = frontier.top();
        frontier.pop();

        if(current==goal) break;

        if(reached.find(current)!=reached.end()) continue;
        reached.insert(current);

        for(Location next : G.neighbors(current)) {
            
            double new_cost = cost_so_far[current] + G.cost(current,next);

            if(cost_so_far.find(next)==cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                came_from[next] = current;
                priority[next] = new_cost + heuristic(next,goal);
                frontier.push(next);
            }
        }
    }
}


int main() {
  GridWithWeights grid = make_diagram4();
  GridLocation start{1, 4}, goal{8, 3};
  std::unordered_map<GridLocation, GridLocation> came_from;
  std::unordered_map<GridLocation, double> cost_so_far;

  a_star_search(grid, start, goal, came_from, cost_so_far);
  //draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);
  std::cout << '\n';
  std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);
  //draw_grid(grid, nullptr, nullptr, &path, &start, &goal);
  std::cout << '\n';
  draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);
}