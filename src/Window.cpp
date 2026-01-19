#include "Window.hpp"

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../include/GridView.hpp"
#include "../include/TileView.hpp"

Window::Window()
    : window(nullptr), renderer(nullptr), running(true), gridView(nullptr) {}

Window::~Window() {
    if (gridView) {
        delete gridView;
        gridView = nullptr;
    }

    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    TTF_Quit();
    SDL_Quit();
}

void Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        running = false;
        return;
    }

    window = SDL_CreateWindow(
        "2048 - Tile Twister",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        running = false;
        return;
    }

    game.addRandomTile();
    game.addRandomTile();
    updateGridView();
}

void Window::renderMessage(const std::string& message) {
    TTF_Font* font = TTF_OpenFont("./assets/Roboto-Bold.ttf", 48);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor{255, 255, 255, 255};

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, message.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    int winW = 640, winH = 480;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);

    const int textW = textSurface->w;
    const int textH = textSurface->h;

    // Background "panel"
    SDL_FRect bgRect{
        static_cast<float>((winW - textW - 40) / 2),
        static_cast<float>((winH - textH - 40) / 2),
        static_cast<float>(textW + 40),
        static_cast<float>(textH + 40)
    };

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_RenderFillRectF(renderer, &bgRect);

    // Text position
    SDL_FRect dstRect{
        static_cast<float>((winW - textW) / 2),
        static_cast<float>((winH - textH) / 2),
        static_cast<float>(textW),
        static_cast<float>(textH)
    };

    SDL_RenderCopyF(renderer, textTexture, nullptr, &dstRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

void Window::render() {
    SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
    SDL_RenderClear(renderer);

    if (gridView) {
        gridView->render(renderer);
    }

    if (game.hasWon()) {
        renderMessage("Tu as gagne !");
    } else if (game.isGameOver()) {
        renderMessage("Tu as perdu !");
    }

    SDL_RenderPresent(renderer);
}

void Window::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            return;
        }

        // Si fin de partie : R pour restart, ESC/Q pour quitter
        if (game.hasWon() || game.isGameOver()) {
            if (event.type == SDL_KEYDOWN) {
                const SDL_Keycode key = event.key.keysym.sym;
                if (key == SDLK_r) {
                    restartGame();
                } else if (key == SDLK_ESCAPE || key == SDLK_q) {
                    running = false;
                }
            }
            continue;
        }

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:  game.move(Direction::LEFT);  break;
                case SDLK_RIGHT: game.move(Direction::RIGHT); break;
                case SDLK_UP:    game.move(Direction::UP);    break;
                case SDLK_DOWN:  game.move(Direction::DOWN);  break;
                default: break;
            }
            updateGridView();
        }
    }
}

void Window::loop() {
    while (running) {
        handleEvents();
        render();
        SDL_Delay(16);
    }
}

void Window::updateGridView() {
    if (gridView) {
        delete gridView;
        gridView = nullptr;
    }

    const int cellSize = 100;
    const int gridW = 4 * cellSize;
    const int gridH = 4 * cellSize;

    int winW = 640, winH = 480;
    if (renderer) {
        SDL_GetRendererOutputSize(renderer, &winW, &winH);
    }

    const int offsetX = (winW - gridW) / 2;
    const int offsetY = (winH - gridH) / 2;

    std::vector<TileView> tileViews;
    Grid& grid = game.getGrid();

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Tile* tile = grid.getTile(i, j);
            if (tile) {
                const int val = tile->getValue();
                tileViews.emplace_back(
                    offsetX + j * cellSize,
                    offsetY + i * cellSize,
                    cellSize,
                    cellSize,
                    val
                );
            }
        }
    }

    gridView = new GridView(offsetX, offsetY, gridW, gridH, tileViews);
}

void Window::restartGame() {
    if (gridView) {
        delete gridView;
        gridView = nullptr;
    }

    game = Game();
    game.addRandomTile();
    game.addRandomTile();
    updateGridView();
}
