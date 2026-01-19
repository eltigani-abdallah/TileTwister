
#pragma once
#include <SDL.h>

#include "Game.hpp"
#include "GridView.hpp"

class Window {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  Game game;
  GridView* gridView;
  bool running;

  void renderMessage(const std::string& message); 

 public:
  Window();
  ~Window();
  void init();
  void render();
  void handleEvents();
  void loop();
  void updateGridView();
  void restartGame();

};
