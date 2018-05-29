#pragma once
#include <iostream>
#include "Node.h"
#include <exception>
#include <list>
#include <fstream>

using namespace std;

struct RGB {
<<<<<<< HEAD
    uint8_t red, green, blue;
public:
    RGB() {}
    RGB(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {}
};

static int counter=1;

=======
  uint8_t red, green, blue;
public:
  RGB() {}
  RGB(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {}
};

>>>>>>> 90365b28e1c4cfee7b517bd13b00bb844cacabfd
class Board
{
public:
    int rows;
    Node **game;
    Board();
    Board(int r);
    Board(const Board& other);
    ~Board();
    string draw(int n);
    Node& operator[](list<int> list);
    Board& operator=(const Board& b);
    Board& operator=(char c);
    friend istream &operator>>(istream &in,Board &b);
    friend ostream &operator<<(ostream &out, const Board &b);
};

class IllegalCoordinateException : public exception
{
    int a,b;
public:
    void setA(int row){
        this->a=row;
    }
    void setB(int col){
        this->b=col;
    }
    string theCoordinate ()const
    {
        return to_string(a)+","+to_string(b);
    }
};

class IllegalCharException : public exception
{
    char input;

public:
    char theChar()const
    {
        return input;
    }
    void setInput(int c){input=c;}
};