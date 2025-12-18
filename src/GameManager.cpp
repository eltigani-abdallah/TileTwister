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

                window.handleEvents();
                if (window.isCloseRequested()==true) {
                        running = false;
                }
        }


}