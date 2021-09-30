#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "implementation.cpp"



/*  BFS for the char representation of nodes
- Returns a map containing parent locations, so that we can print out paths.
- This implementation also includes an optional stopping distance argument.
*/

template<typename Location, typename Graph>
std::unordered_map<Location,Location> BFS( Graph G,  Location source, Location goal, int stopping_distance = -1 ) {  

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

        //if(v==goal) break; //comment this if you want to explore the full grid

        if(stopping_distance>0){
            if(v.distance==stopping_distance) break;
        }
        //std::cout<<"visiting..."<<v<<'\n';

        for(Location u : G.neighbors(v)) {
            if(reached.find(u)==reached.end()) {

                came_from[u] = v;
                u.distance = v.distance+1;
                frontier.push(u);
                reached.insert(u);
            }
        }
    }
    return came_from;
}

template<typename Location, typename Graph>
void find_path(Graph G, Location source, Location v) { //function that finds the (shortest) path from source to v

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
GridLocation goal{8,8};
auto parents = BFS(grid, start,goal, 5);
draw_grid(grid, nullptr, &parents, nullptr, &start, &goal);
}
