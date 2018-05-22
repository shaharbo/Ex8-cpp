#include <iostream>
using namespace std;

class Node
{
    char val;

public:
    Node();
    Node(char val);
    char getNode() const;
    Node& operator=(char val);
    friend ostream& operator<< (ostream& os, Node& c);
    void setC(char c);
    operator char() const { return val; }
};
inline ostream& operator<< (ostream& os, Node& n)
{
    os << n.getNode();
    return os;
}