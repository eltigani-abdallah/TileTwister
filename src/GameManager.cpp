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

        window.open();

        SDL_Delay(3000);
}