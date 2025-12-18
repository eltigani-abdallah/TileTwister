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


    /**
     * handle events such as closing the window
     */
    void handleEvents();

    //refresh window for new content
    void update();

    //close window
    void close();

    /**
     * check if handleEvents has made a request to close the current window
     * @return true if the window closure was requested
     */
    bool isCloseRequested();








private:
    std::string title;
    int width;
    int height;

    SDL_Window* window;
    bool closeRequest{false};


};


#endif //TILETWISTER_WINDOW_H