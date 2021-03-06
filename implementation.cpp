/*
 Sample code from https://www.redblobgames.com/pathfinding/a-star/
 Copyright 2014 Red Blob Games <redblobgames@gmail.com>
 
 Feel free to use this code in your own projects, including commercial projects
 License: Apache v2.0 <http://www.apache.org/licenses/LICENSE-2.0.html>
*/

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
#include <cstdlib>


struct GridLocation {
  int x, y;
  int distance; //track distance from source
};


/* implement hash function so we can put GridLocation into an unordered_set */

namespace std { //inject into namespace std
template <> struct hash<GridLocation> { //template specialisation
  typedef GridLocation argument_type;
  typedef std::size_t result_type;
  std::size_t operator()(const GridLocation& id) const noexcept {
    return std::hash<int>()(id.x ^ (id.y << 4));
  }
};
}


struct SquareGrid {
  static std::array<GridLocation, 4> DIRS; //Static member variables are shared between all instances of the class

  int width, height;
  std::unordered_set<GridLocation> walls; //stores coordinates of the obstacles

  SquareGrid(int width_, int height_)
     : width(width_), height(height_) {}

  bool in_bounds(GridLocation id) const { //function to check whether a point lies within the grid
    return 0 <= id.x && id.x < width
        && 0 <= id.y && id.y < height;
  }

  //checks if a point is passable by looking at the set of walls
  bool passable(GridLocation id) const { 
    return walls.find(id) == walls.end();
  }

  //function that returns the neighbouring points of a given point
  std::vector<GridLocation> neighbors(GridLocation id) const { 

    std::vector<GridLocation> results;

    for (GridLocation dir : DIRS) { //find adjacent coordinates
      GridLocation next{id.x + dir.x, id.y + dir.y};
      if (in_bounds(next) && passable(next)) {
        results.push_back(next);
      }
    }

    if ((id.x + id.y) % 2 == 0) {
      // see "Ugly paths" section for an explanation:
      std::reverse(results.begin(), results.end());
    }

    return results;
  }

};

std::array<GridLocation, 4> SquareGrid::DIRS = { //static member variables must be defined in global scope, and should be done using scope operator (::)
  /* East, West, North, South */
  GridLocation{1, 0}, GridLocation{-1, 0},
  GridLocation{0, -1}, GridLocation{0, 1}
};

// Helpers for GridLocation

bool operator == (GridLocation a, GridLocation b) {
  return a.x == b.x && a.y == b.y;
}

bool operator != (GridLocation a, GridLocation b) {
  return !(a == b);
}

bool operator < (GridLocation a, GridLocation b) {
  return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc) {
  out << '(' << loc.x << ',' << loc.y << ')';
  return out;
}

// This outputs a grid. Pass in a distances map if you want to print
// the distances, or pass in a point_to map if you want to print
// arrows that point to the parent location, or pass in a path vector
// if you want to draw the path.
template<class Graph>
void draw_grid(const Graph& graph,
               std::unordered_map<GridLocation, double>* distances=nullptr,
               std::unordered_map<GridLocation, GridLocation>* point_to=nullptr,
               std::vector<GridLocation>* path=nullptr,
               GridLocation* start=nullptr,
               GridLocation* goal=nullptr) {
  const int field_width = 3;
  std::cout << std::string(field_width * graph.width, '_') << '\n'; //prints consecutive copies of '_'
  for (int y = 0; y != graph.height; ++y) {
    for (int x = 0; x != graph.width; ++x) {
      GridLocation id {x, y};
      if (graph.walls.find(id) != graph.walls.end()) { // first check if cell is a wall
        std::cout << std::string(field_width, '#');
      } else if(graph.forests.find(id) !=graph.forests.end() && !distances) { //Check if cell is a forest
        std::cout << std::string(field_width,'F');
      }else if (start && id == *start) { // check for the source node
        std::cout << " A ";
      } else if (goal && id == *goal) { //check for destination node
        std::cout << " Z ";
      } else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) { //print the shortest paths??
        std::cout << " @ ";
      } else if (point_to != nullptr && point_to->count(id)) {
        GridLocation next = (*point_to)[id];
        if (next.x == x + 1) { std::cout << " > "; }
        else if (next.x == x - 1) { std::cout << " < "; }
        else if (next.y == y + 1) { std::cout << " v "; }
        else if (next.y == y - 1) { std::cout << " ^ "; }
        else { std::cout << " * "; }
      } else if (distances != nullptr && distances->count(id)) {
        std::cout << ' ' << std::left << std::setw(field_width - 1) << (*distances)[id];
      } else {
        std::cout << " . "; //empty point
      }
    }
    std::cout << '\n';
  }
  std::cout << std::string(field_width * graph.width, '~') << '\n';
}

// Use this function to add some obstacles that cannot be passed
void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2) { 
  for (int x = x1; x < x2; ++x) {
    for (int y = y1; y < y2; ++y) {
      grid.walls.insert(GridLocation{x, y});
    }
  }
}

SquareGrid make_diagram1() {
  SquareGrid grid(30, 15);
  add_rect(grid, 3, 3, 5, 12);
  add_rect(grid, 13, 4, 15, 15);
  add_rect(grid, 21, 0, 23, 7);
  add_rect(grid, 23, 5, 26, 7);
  return grid;
}


/*
  Now With Weights
-------------------------------------------
*/

// A grid of forest tiles, with uniform weight of 5
struct GridWithWeights: SquareGrid {
  std::unordered_set<GridLocation> forests;
  GridWithWeights(int w, int h): SquareGrid(w, h) {}
  double cost(GridLocation from_node, GridLocation to_node) const {
    return forests.find(to_node) != forests.end()? 5 : 1;
  }
};

GridWithWeights make_diagram4() {
  GridWithWeights grid(10, 10);
  add_rect(grid, 1, 7, 4, 9); //add some walls
  typedef GridLocation L;
  grid.forests = std::unordered_set<GridLocation> {
    L{3, 4}, L{3, 5}, L{4, 1}, L{4, 2},
    L{4, 3}, L{4, 4}, L{4, 5}, L{4, 6},
    L{4, 7}, L{4, 8}, L{5, 1}, L{5, 2},
    L{5, 3}, L{5, 4}, L{5, 5}, L{5, 6},
    L{5, 7}, L{5, 8}, L{6, 2}, L{6, 3},
    L{6, 4}, L{6, 5}, L{6, 6}, L{6, 7},
    L{7, 3}, L{7, 4}, L{7, 5}
  };
  return grid;
}

template<typename Location>
std::vector<Location> reconstruct_path(
   Location start, Location goal,
   std::unordered_map<Location, Location> came_from
) {
  std::vector<Location> path;
  Location current = goal;
  while (current != start) {
    path.push_back(current);
    current = came_from[current];
  }
  path.push_back(start); // optional
  std::reverse(path.begin(), path.end());
  return path;
}


inline double heuristic(GridLocation a, GridLocation b) {
 return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

