#include "../include/GameManager.hpp"

GameManager::GameManager(std::string title, int width, int height):
window(title, width, height)
{


}

void GameManager::update() {


}



void GameManager::render() {


}

void GameManager::run() {
        bool running = true;
        window.open();

        while (running) {
                //handleInput returns true if everything is ok, false if the x button is clicked
                if (InputManager::handleInput()==false) {
                        running = false; //switch running to false and go back out to main
                }

        }


}

Window GameManager::getWindow() {
        return window;
}

void GameManager::endProg() {
        window.close();
        SDL_Quit();
        exit(0);
}
