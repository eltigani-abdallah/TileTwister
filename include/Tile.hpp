#ifndef TILE_HPP
#define TILE_HPP

class Tile {

public:
    Tile(int value, int posX, int posY);

    void combine();
    bool canMove();


    //↓ getters ↓
    int getValue();
    int getPosX();
    int getPosY();
    //↑ getters ↑

    // ↓ setters ↓
    void setValue(int value);
    void setPosX(int posX);
    void setPosY(int posY);
    //↑ setters ↑

private:
    int value;
    int posX;
    int posY;


};



#endif