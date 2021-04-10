#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL.h"
#include "renderer.h"
#include <vector>
#include <complex>
#include <tuple>

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
  Display(const std::size_t screen_dim,
          const double x_low,
          const double x_high,
          const double y_low,
          const double y_high,
          const std::size_t max_iters)
    : MAX_ITERS(max_iters) {
      fract.x_min = x_low;
      fract.x_max = x_high;
      fract.y_min = y_low;
      fract.y_max = y_high;
      
      scr.x_min = 0;
      scr.x_max = screen_dim; 
      scr.y_min = 0; 
      scr.y_max = screen_dim; 
    };
  void Run(Renderer &renderer);
  void Mandelbrot(Renderer &renderer);
  
  void calculate_number_iterations();
  std::complex<double> scale(std::complex<double> c);
  void map_color(std::complex<double> c);
  void set_color(int iter);

 private:
  Scr<int> scr;
  Fract<double> fract;
  std::vector<std::tuple<int, int, int>> colors;
  const int MAX_ITERS; 
  void Update();
};

#endif