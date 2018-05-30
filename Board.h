#pragma once
#include <iostream>
#include "Node.h"
#include <exception>
#include <list>
#include <fstream>
#include <ctime>
#include <math.h>

using namespace std;

struct RGB {
uint8_t red, green, blue;
public:
    RGB() {}
    RGB(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {}
};

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