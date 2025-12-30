#ifndef TILETWISTER_WINDOW_H
#define TILETWISTER_WINDOW_H
#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <string>



class Window {

public:
    /**
     * initialize window parameters, to create a window, use Window::Open
     * @param title window title
     * @param width window width
     * @param height window height
     */
    Window(std::string title, int width, int height);

    /**
     * create and open an SDL_Window. params are initialized in Window::Window
     * @return resizable SDL_Window
     */
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