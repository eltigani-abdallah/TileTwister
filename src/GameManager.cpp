#include "../include/GameManager.hpp"

GameManager::GameManager(std::string title, int width, int height):
window(title, width, height)
{


}

void GameManager::update() {


}


void GameManager::handleEvents() {

        InputManager::handleInput();
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

Window GameManager::getWindow() {
        return window;
}

void GameManager::endProg() {
        window.close();
        SDL_Quit();
}
