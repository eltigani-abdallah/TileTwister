#include "../include/InputManager.hpp"


void InputManager::handleInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case (SDL_EVENT_QUIT):
                exit(0);
            case (SDL_EVENT_KEY_UP):
                SDL_Log("%d was just released", event.key.key);
                break;

        }
    }
}
