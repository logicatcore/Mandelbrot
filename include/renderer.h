#ifndef RENDERER_H
#define RENDERER_H

#include <tuple>
#include <vector>
#include <memory>
#include <opencv2/highgui/highgui.hpp>

class Renderer {
 public:
  Renderer(unsigned int screen_dim = 600);
  ~Renderer(){};

  void Render(std::shared_ptr<std::vector<std::tuple<int, int, int>>> clrs, cv::Rect &crop, int &key);

 private:
  cv::Mat img;
  std::string windowName{"Mandelbrot"}; 
  const std::size_t screen_dim;
};

#endif