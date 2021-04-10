#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL.h"
#include "renderer.h"
#include <vector>
#include <complex>
#include <tuple>
#include <memory>

// window details in pixel units
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

// mapped complex plane bounds
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

using std::size_t;

class Display {
 public:
  Display(const size_t screen_dim,
          const size_t order,
          const double x_low,
          const double x_high,
          const double y_low,
          const double y_high,
          const size_t max_iters)
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

      colors = std::make_shared<std::vector<std::tuple<size_t, size_t, size_t>>>(screen_dim * screen_dim);
    };
  void Run(Renderer &renderer);
  void Mandelbrot(size_t xMin, size_t yMin, size_t xMax, size_t yMax, 
                  size_t sub_domain_width, size_t sub_domain_height, size_t cores, 
                  std::shared_ptr<std::vector<std::tuple<size_t, size_t, size_t>>> clrs, size_t domain_no) ;

  std::complex<double> fullDomainScale(std::complex<double> c);
  std::complex<double> scale(std::complex<double> c, size_t &scr_x_max, size_t &scr_y_max, size_t n_cores);
  void map_color(std::complex<double> c, size_t &&idx, std::shared_ptr<std::vector<std::tuple<size_t, size_t, size_t>>> &clr);
  void set_color(size_t iter, size_t idx, std::shared_ptr<std::vector<std::tuple<size_t, size_t, size_t>>> &clr);
 
 private:
  Scr<size_t> scr;
  Fract<double> fract;
  std::shared_ptr<std::vector<std::tuple<size_t, size_t, size_t>>> colors;
  const size_t MAX_ITERS, SET_ORDER; 
};

#endif