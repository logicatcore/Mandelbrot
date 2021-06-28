#ifndef DISPLAY_H
#define DISPLAY_H

// #include "SDL.h"
#include "renderer.h"
#include <vector>
#include <complex>
#include <tuple>
#include <memory>
#include <cstdint>

// window details in pixel units
template <typename T>
struct Bounds{
  Bounds(T minx, T maxx, T miny, T maxy){
    x_min = minx;
    x_max = maxx;
    y_min = miny;
    y_max = maxy;
  }
  T x_min, x_max, y_min, y_max;
  T getWidth(){
    return x_max - x_min;
  }
  T getHeight(){
    return y_max - y_min;
  }
};

using std::size_t;
class Display {
 public:
  Display(size_t screen_dim = 600,
          size_t order = 2,
          double x_low = -2.2,
          double x_high = 1.2,
          double y_low = -1.7,
          double y_high = 1.7,
          size_t max_iters = 100)
    : MAX_ITERS(max_iters),
      SET_ORDER(order),
      fract(x_low, x_high, y_low, y_high),
      scr(0, screen_dim, 0, screen_dim) {
      colors = std::make_shared<std::vector<std::tuple<int, int, int>>>(screen_dim * screen_dim);
    };
  void Run(Renderer &renderer);

 private:
  Bounds<size_t> scr;
  Bounds<double> fract;
  cv::Rect zoomRect{0, 0, 0, 0};
  std::shared_ptr<std::vector<std::tuple<int, int, int>>> colors;
  const size_t MAX_ITERS, SET_ORDER; 

  void Mandelbrot(size_t xMin, size_t yMin, size_t xMax, size_t yMax, 
                size_t sub_domain_width, size_t sub_domain_height, size_t cores, 
                std::shared_ptr<std::vector<std::tuple<int, int, int>>> clrs, size_t domain_no) ;

  std::complex<double> scale(std::complex<double> c);
  std::complex<double> scale(std::complex<double> c, size_t &scr_x_max, size_t &scr_y_max, size_t n_cores);
  void map_color(std::complex<double> c, size_t &&idx, std::shared_ptr<std::vector<std::tuple<int, int, int>>> &clr);
  void set_color(size_t iter, size_t idx, std::shared_ptr<std::vector<std::tuple<int, int, int>>> &clr);
 
};

#endif