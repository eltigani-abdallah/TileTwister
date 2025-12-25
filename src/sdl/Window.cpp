#include "../include/sdl/Window.hpp"

Window::Window(std::string title, int width, int height){

    this->title = title;
    this->width = width;
    this->height =height;



}


SDL_Window* Window::open() {
    window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_RESIZABLE);
    return window;
}

void Window::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case (SDL_EVENT_QUIT):
                closeRequest=true;
                close();
                break;

        }
    }



}

void Window::close() {


    SDL_DestroyWindow(window);

}

bool Window::isCloseRequested() {
    return closeRequest;
}