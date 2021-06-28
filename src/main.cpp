#include <iostream>
#include "../include/renderer.h"
#include "../include/display.h"

int main(int argc, char **args) {
    constexpr double cxMin{-2.2}, cxMax{1.2}, cyMin{-1.7}, cyMax{1.7};

    // defualts
    std::size_t kScreenDim{600};
    std::size_t maxIter{600};
    std::size_t MandelbrotSetOrder{2};

    if (argc > 1 & argc == 4){
        char *eptr;
        kScreenDim = std::strtol(args[1], &eptr, 10);         // only square windows
        maxIter = std::strtol(args[2], &eptr, 10);            // max iterations
        MandelbrotSetOrder = std::strtol(args[3], &eptr, 10); // max iterations
    }

    Renderer renderer(kScreenDim);
    Display display(kScreenDim, MandelbrotSetOrder, cxMin, cxMax, cyMin, cyMax, maxIter);
    display.Run(renderer);

    return 0;
}