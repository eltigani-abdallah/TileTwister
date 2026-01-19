#include "../include/TileView.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

TileView::TileView(int x, int y, int width, int height, int value)
    : GameObject(x, y, width, height), value(value) {}

void TileView::setValue(int newValue) { value = newValue; }
int TileView::getValue() { return value; }

void TileView::render(SDL_Renderer* renderer) {
  // Draw tile rectangle (float version)
  SDL_FRect rect{
      static_cast<float>(x),
      static_cast<float>(y),
      static_cast<float>(width),
      static_cast<float>(height)
  };

  SDL_SetRenderDrawColor(renderer, 200, 180, 140, 255);
  SDL_RenderFillRectF(renderer, &rect);

  SDL_SetRenderDrawColor(renderer, 120, 110, 90, 255);
  SDL_RenderDrawRectF(renderer, &rect);

  // Draw value as text
  if (value <= 0) return;

  TTF_Font* font = TTF_OpenFont("./assets/Roboto-Bold.ttf", height / 2);
  if (!font) {
    std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    return;
  }

  SDL_Color textColor{50, 50, 50, 255};
  const std::string valStr = std::to_string(value);

  SDL_Surface* textSurface = TTF_RenderText_Blended(font, valStr.c_str(), textColor);
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

  const int textW = textSurface->w;
  const int textH = textSurface->h;

  SDL_FRect dstRect{
      static_cast<float>(x + (width - textW) / 2),
      static_cast<float>(y + (height - textH) / 2),
      static_cast<float>(textW),
      static_cast<float>(textH)
  };

  // SDL2: use RenderCopyF for float rects
  SDL_RenderCopyF(renderer, textTexture, nullptr, &dstRect);

  SDL_DestroyTexture(textTexture);
  SDL_FreeSurface(textSurface);
  TTF_CloseFont(font);
}
