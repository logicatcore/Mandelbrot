#include <iostream>
#include "../include/renderer.h"
#include "../include/display.h"

int main(int argc, char **args) {
    std::size_t kScreenDim{600}; // only square windows
    constexpr double cxMin{-2.2}, cxMax{1.2}, cyMin{-1.7}, cyMax{1.7};
    std::size_t maxIter{600}; // max iterations
    std::size_t MandelbrotSetOrder{2}; // max iterations

    if (argc > 1 & argc == 4){
        char *eptr;
        kScreenDim = std::strtol(args[1], &eptr, 10);
        maxIter = std::strtol(args[2], &eptr, 10);
        MandelbrotSetOrder = std::strtol(args[3], &eptr, 10);
    }

    Renderer renderer(kScreenDim);
    Display display(kScreenDim, MandelbrotSetOrder, cxMin, cxMax, cyMin, cyMax, maxIter);
    display.Run(renderer);

    return 0;
}