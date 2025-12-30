#include "../include/GameManager.hpp"

GameManager::GameManager(std::string title, int width, int height):
window(title, width, height)
{

}

void GameManager::update() {


}


void GameManager::handleEvents() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
                switch (event.type) {
                        case (SDL_EVENT_QUIT):
                                window.close();
                                exit(0);
                                break;

                }
        }
}

void GameManager::render() {


}

void GameManager::run() {
        bool running = true;
        window.open();

        while (running) {

                handleEvents();

        }


}