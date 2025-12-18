#include "GameManager.hpp"

int main() {
    // add a | if you want to initialize something else along with the video initialization
    // ex: SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("failed to initialize, %s", SDL_GetError());
        return 1;
    }









    SDL_Quit();
    return 0;
}