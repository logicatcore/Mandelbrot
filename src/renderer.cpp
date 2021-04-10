#include "../include/renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_dim)
    : screen_dim(screen_dim),
      wx_max(screen_dim),
      wy_max(screen_dim) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_dim,
                                screen_dim, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  // window title
  SDL_SetWindowTitle(sdl_window, "Mandelbrot Set");
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(std::vector<std::tuple<int, int, int>> &clrs) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  int k = 0;
  for(int i = wy_min; i < wy_max; ++i) {
		for(int j = wx_min; j < wx_max; ++j) {
      SDL_SetRenderDrawColor(sdl_renderer, std::get<0>(clrs[k]), std::get<1>(clrs[k]), std::get<2>(clrs[k]), 255);
      SDL_RenderDrawPoint(sdl_renderer, j, i);

      k += 1;
    }
  }
  
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}


