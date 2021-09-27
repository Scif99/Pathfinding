#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "implementation.cpp"


struct graph {
    std::unordered_map<char, std::vector<char>> edges;

    std::vector<char> neighbours(char v) {
        return edges[v];
        }
};

std::unordered_map<char,char> BFS( graph G,  char source ) {

    std::queue<char> frontier;
    frontier.push(source);

    std::unordered_set<char> reached;
    reached.insert(source);

    std::unordered_map<char,char> came_from;
    //dont add source...


    while(!frontier.empty()) {
        char v = frontier.front();
        frontier.pop();
        //std::cout<<"visiting..."<<v<<'\n';

        for(char u : G.neighbours(v)) {
            if(reached.find(u)==reached.end()) {

                came_from[u] = v;
                frontier.push(u);
                reached.insert(u);
            }
        }
    }

    return came_from;
}

void find_path(graph G, char source, char v) { //function that finds the (shortest) path from source to v
    auto parent = BFS(G,source); 

     char x = v;

    while(x) { //follow parents backwards from v
        std::cout<<x<<'\n';
        x = parent[x];
    }
    
}

int main() {
graph example_graph {{
    {'A', {'B'}},
    {'B', {'C'}},
    {'C', {'B', 'D', 'F'}},
    {'D', {'C', 'E'}},
    {'E', {'F'}},
    {'F', {}},
  }};
 

find_path(example_graph, 'A', 'F');

   
SquareGrid grid = make_diagram1();
draw_grid(grid);
}
