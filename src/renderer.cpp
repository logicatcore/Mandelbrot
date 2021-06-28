#include "../include/renderer.h"
#include <iostream>
#include <string>
#include <algorithm>

typedef cv::Point3_<uint8_t> Pixel;

Renderer::Renderer(unsigned int screen_dim)
    : screen_dim(screen_dim)
  {
    img.create(cv::Size(screen_dim, screen_dim), CV_8UC3);
    cv::namedWindow(windowName, cv::WINDOW_KEEPRATIO);
    cv::resizeWindow(windowName, screen_dim, screen_dim);
  }

void Renderer::Render(std::shared_ptr<std::vector<std::tuple<int, int, int>>> clrs, cv::Rect &crop, int &key) {

  std::for_each((*clrs).begin(), (*clrs).end(), [this](std::tuple<int, int, int> &clr){
    static int r = 0, c = 0;
    if (c == this->screen_dim){
      c = 0;
    }
    this->img.at<cv::Vec3b>(r, c)[2] = std::get<0>(clr);
    this->img.at<cv::Vec3b>(r, c)[1] = std::get<1>(clr); 
    this->img.at<cv::Vec3b>(r, c)[0] = std::get<2>(clr);
    r++;
    if (r == this->screen_dim){
      r = 0;
      c++;
    }
  });

  // Update Screen
  cv::imshow(windowName, img);
  // allow time to update screen
  cv::waitKey(100);

  // handle proper exit sequence
  std::cout << "Press 'q' to quit or 'z' to continue and zoom in the set: ";
  char keyStroke;
  std::cin >> keyStroke;

  if (keyStroke == 'z'){
    crop = cv::selectROI(windowName, img);
    // if changed the mind about zooming
    if (crop.width == 0 && crop.height == 0){
      key = 'q';
      cv::destroyWindow(windowName);
    }
  }
  else if(keyStroke == 'q') {
    key = 'q';
    cv::destroyWindow(windowName);
  }
}


