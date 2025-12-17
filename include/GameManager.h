#ifndef TILETWISTER_GAMEMANAGER_H
#define TILETWISTER_GAMEMANAGER_H
#include "GameState.h"



class GameManager {

public:
    //Constructor
    GameManager();

    //handle physics and update screen
    void update();

    //render graphics
    void render();

    //run game
    void run();




private:
    // enum to be added later to figure out which state the game is in
    GameState state;



};


#endif //TILETWISTER_GAMEMANAGER_H