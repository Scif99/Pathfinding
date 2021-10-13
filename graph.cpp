#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "implementation.cpp"




// BFS implementation
// Returns a table of {location: parent}
template<typename Location, typename Graph>
std::unordered_map<Location,Location> BFS( Graph G,  Location source, Location goal, bool early_stop = true) {  

    std::queue<Location> frontier;
    frontier.push(source);

    std::unordered_set<Location> reached;
    reached.insert(source);

    std::unordered_map<Location,Location> came_from;
    //dont add source...

    source.distance = 0;

    while(!frontier.empty()) {
        Location v = frontier.front();
        frontier.pop();

        if(v==goal && early_stop) break; 

        //std::cout<<"visiting..."<<v<<'\n';

        for(Location u : G.neighbors(v)) {
            if(reached.find(u)==reached.end()) {

                came_from[u] = v; //track parent node
                u.distance = v.distance+1;
                frontier.push(u);
                reached.insert(u);
            }
        }
    }
    return came_from;
}

// Function that finds and prints the (shortest) path from source to v
template<typename Location, typename Graph>
void find_path(Graph G, Location source, Location v) { 

    std::unordered_map<Location,Location> parent = BFS(G,source); 

     Location x = v;

    while(x) { //follow parents backwards from v
        std::cout<<x<<'\n';
        x = parent[x];
    }
    
}



int main() {

SquareGrid grid = make_diagram1();
GridLocation start{7,8};
GridLocation goal{10,8};
auto parents = BFS(grid, start,goal, false);
draw_grid(grid, nullptr, &parents, nullptr, &start, &goal);
}
