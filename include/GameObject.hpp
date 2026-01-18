#ifndef TILETWISTER_GAMEOBJECT_H
#define TILETWISTER_GAMEOBJECT_H
#include <iostream>


class GameObject {
    public:
        virtual void setVal(int val) = 0;
        virtual int getVal() const = 0;

        virtual std::pair<int,int> getPos() const = 0;
        virtual void setPos(int x, int y) = 0;
        virtual int getXPos() const = 0;
        virtual int getYPos() const = 0;

        virtual bool hasMerged() const = 0;
        virtual void setMerged(bool status) = 0;

};


#endif //TILETWISTER_GAMEOBJECT_H