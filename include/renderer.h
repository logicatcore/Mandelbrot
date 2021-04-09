#ifndef RENDERER_H
#define RENDERER_H

#include <tuple>
#include <vector>
#include "SDL.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_dim);
  ~Renderer();

  void Render(std::vector<std::tuple<int, int, int>> &clrs);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_dim;
};

#endif