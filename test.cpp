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


class point {
    int x,y;
    static std::string name;

public:
    static std::string get_name() {return name;}
    
};

 std::string point::name{"Soleh"};

int main(){ 
    std::string s = "C String";
    s = "New String!";
    std::cout<<s;

}