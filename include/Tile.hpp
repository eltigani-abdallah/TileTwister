
#pragma once
#include <iostream>

class Tile {
private:
    int value;
    int x;
    int y;

public:
    Tile(int v, int posX, int posY);
     int getValue()const;
     void setValue(int newVal); 
     std::pair<int, int> getPosition() const;
     void setPosition(int newX, int newY);


};
