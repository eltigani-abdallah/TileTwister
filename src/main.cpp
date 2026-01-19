#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <iostream>
#include "../include/Window.hpp"

int main() {
    Window window;
    window.init();
    window.loop();
    
    
    return 0;
}