#include <iostream>
#include "../include/renderer.h"
#include "../include/display.h"

int main() {
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{400};
    constexpr std::size_t kScreenHeight{400};
    constexpr double cxMin{-2.2}, cxMax{1.2}, cyMin{-1.7}, cyMax{1.7};
    constexpr std::size_t maxIter{100};

    Renderer renderer(kScreenWidth, kScreenHeight);
    Display display(kScreenWidth, kScreenHeight, cxMin, cxMax, cyMin, cyMax, maxIter);
    display.Run(renderer);

    return 0;
}