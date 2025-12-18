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
    SDL_Window* open();

    //refresh window for new content
    void update();

    //close window
    void close();








private:
    std::string title;
    int width;
    int height;

    SDL_Window* window;


};


#endif //TILETWISTER_WINDOW_H