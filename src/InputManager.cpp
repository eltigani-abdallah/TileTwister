#include "../include/InputManager.hpp"


bool InputManager::handleInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case (SDL_EVENT_QUIT):
                return false; //if the x button was clicked return false and handle the rest in GameManager
            case (SDL_EVENT_KEY_UP):
                SDL_Log("%d was just released", event.key.key);
                break;

        }
    }



    return true; //if everything is working fine then return true
}
