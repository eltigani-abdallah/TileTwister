#ifndef TILETWISTER_GAMEMANAGER_H
#define TILETWISTER_GAMEMANAGER_H
#include "sdl/Window.hpp"

#include "GameState.hpp"




class GameManager {

public:
    /**
     * Constructor for the GameManager
     * @param title  window title
     * @param width window width
     * @param height window height
     */
    GameManager(std::string title, int width, int height);


    void update();

    //render graphics
    void render();

    /**
     * run the game
     */
    void run();




private:
    // enum to be added later to figure out which state the game is in
    GameState state;

    //window for program to render on
    Window window;



};


#endif //TILETWISTER_GAMEMANAGER_H