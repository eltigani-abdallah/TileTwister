#include "GameManager.hpp"

int main() {
    // add a | if you want to initialize something else along with the video initialization
    // ex: SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("failed to initialize SDL3 video → %s", SDL_GetError());
        return 1;
    }

    GameManager gm("Hello, World!", 500, 500);


    gm.run();








    gm.getWindow().close();
    SDL_Quit();
    return 0;
}