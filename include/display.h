#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL.h"
#include "renderer.h"
#include <vector>
#include <complex>
#include <tuple>
#include <memory>

template <typename T>
struct Scr{
  T x_min, x_max, y_min, y_max;
  T getWidth(){
    return x_max - x_min;
  }
  T getHeight(){
    return y_max - y_min;
  }
};

template <typename T>
struct Fract{
  T x_min, x_max, y_min, y_max;
  T getWidth(){
    return x_max - x_min;
  }
  T getHeight(){
    return y_max - y_min;
  }
};

class Display {
 public:
  Display(std::size_t screen_dim = 600,
          std::size_t order = 2,
          double x_low = -2.2,
          double x_high = 1.2,
          double y_low = -1.7,
          double y_high = 1.7,
          std::size_t max_iters = 100)
    : MAX_ITERS(max_iters),
      SET_ORDER(order) {
      fract.x_min = x_low;
      fract.x_max = x_high;
      fract.y_min = y_low;
      fract.y_max = y_high;
      
      scr.x_min = 0;
      scr.x_max = screen_dim; 
      scr.y_min = 0; 
      scr.y_max = screen_dim;

      colors = std::make_shared<std::vector<std::tuple<int, int, int>>>(screen_dim * screen_dim);
    };
  void Run(Renderer &renderer);


 private:
  Scr<int> scr;
  Fract<double> fract;
  std::shared_ptr<std::vector<std::tuple<int, int, int>>> colors;
  const int MAX_ITERS, SET_ORDER; 

  void Mandelbrot(Renderer &renderer);
  void calculate_number_iterations();
  std::complex<double> scale(std::complex<double> c);
  void map_color(std::complex<double> c, int &idx);
  void set_color(int iter, int &idx);
};

#endif