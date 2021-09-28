#include <iostream>
#include <string>
#include <unordered_map>

template <class T>
struct myPair {
    T x;
    T y;

    myPair(T a, T b) : x{a}, y{b} {}

    bool operator==(const myPair& other ) { //overload the equality operator
        return (x ==other.x && y == other.y);
    }

    void increase() { // function that increments each element
        ++x;
        ++y;
    }

    void print() {
        std::cout<<x<<'\n'<<y;
    }
};

template <>
struct myPair<char> {
    char x;
    char y;
    
    myPair(char a, char b) : x{a}, y{b} {}

    bool operator==(const myPair& other) { //this equality operator is necessary for implementing a hashing function
        return (x ==other.x && y==other.y);
    }

    void increase() {
        x = toupper(x);
        y = toupper(y);
    }
    void print() {
        std::cout<<x<<'\n'<<y;
    }
};

namespace std { 
    template<> 
    struct hash<myPair<char>> {

        size_t operator()(const myPair<char>& id) const { //this operator overload defines the hash function
            return ((hash<char>()(id.x)^ (hash<char>()(id.y) << 1)) >> 1);
        }

    };
}





int main() {

    myPair<int> one = myPair<int> (1,2);
    myPair<char> two = myPair<char> ('a','b');

    one.increase();
    two.increase();
    one.print();
    two.print();


}

