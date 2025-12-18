#ifndef TILETWISTER_WINDOW_H
#define TILETWISTER_WINDOW_H
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <string>

class Window {

public:

    //initialize window class
    Window(std::string title, int width, int height);

    //open window
    void open();

    //close window
    void close();






private:

    const int WIDTH;
    const int HEIGHT;


};


#endif //TILETWISTER_WINDOW_H