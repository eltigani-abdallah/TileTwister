#include "../include/GridView.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


GridView::GridView(int x, int y, int width, int height,
                   const std::vector<TileView>& tiles)
    : GameObject(x, y, width, height), tiles(tiles) {}


void GridView::render(SDL_Renderer* renderer) {
  SDL_FRect rect{
      static_cast<float>(x),
      static_cast<float>(y),
      static_cast<float>(width),
      static_cast<float>(height)
  };

  SDL_SetRenderDrawColor(renderer, 180, 170, 160, 255);
  SDL_RenderFillRectF(renderer, &rect);

  for (TileView& tile : tiles) {
    tile.render(renderer);
  }
}
