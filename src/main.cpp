#include <iostream>
#include "../include/renderer.h"
#include "../include/display.h"

int main() {
    constexpr std::size_t kScreenDim{600}; // only square windows
    constexpr double cxMin{-2.2}, cxMax{1.2}, cyMin{-1.7}, cyMax{1.7};
    constexpr std::size_t maxIter{600}; // max iterations
    constexpr std::size_t MandelbrotSetOrder{2}; // max iterations

    Renderer renderer(kScreenDim);
    Display display(kScreenDim, MandelbrotSetOrder, cxMin, cxMax, cyMin, cyMax, maxIter);
    display.Run(renderer);

    return 0;
}