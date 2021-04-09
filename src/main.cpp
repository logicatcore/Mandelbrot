#include <iostream>
#include "../include/renderer.h"
#include "../include/display.h"

int main() {
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenDim{400}; // only square windows
    constexpr double cxMin{-2.2}, cxMax{1.2}, cyMin{-1.7}, cyMax{1.7};
    constexpr std::size_t maxIter{100};

    Renderer renderer(kScreenDim);
    Display display(kScreenDim, cxMin, cxMax, cyMin, cyMax, maxIter);
    display.Run(renderer);

    return 0;
}