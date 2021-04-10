# Udacity CPP Nanodegree: Capstone Mandelbrot Project

This Capstone Project is meant to show the students(here mine) ability to integrate what has been learned throughout C++ Nanodegree program. This project demonstrates that I can independently create applications using a wide range of C++ features.

## Mandelbrot set
The Mandelbrot set is the set of complex numbers c for which the function `f(z) = z^2 + c` does not **diverge** when iterated from `z = 0`, i.e., for which the sequence `f(0)`, `f(f(0))`, etc., remains bounded in absolute value.

This application enables investigating the Mandelbrot set flexibily and is capable of scaling to high precision investigation when proportional comutation power is availablle. This Repo consists of two versions of the same application-
1. The first version maps each pixel to a point on the complex plane sequentially i.e. serial program execution. On branch **serial_computation**.
2. The second version first divides the entire window into sub windows based on the supported hardware concurrenct and then maps each pixel in each sub window to the complex plane parallely to increase the speed. The increase in speed due to parallel execution is clearly evident during usage. On branch **parallel_computation**.

## Application preview

![](./main.png)

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL library
  * Installation on linux machines `sudo apt-get install libsdl2-dev`

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Mandelbrot`

## Usage instructions

1. The application window is capable of handling zoom requests but without a visual feedback of a dynamic zooming rectangle
2. To zoom, draw an imaginary rectangle by moving the left mouse key pressed from top left corner to bottom right corner
3. The drawn rectangle is turned into a square internally to maintain aspect ratio
4. Depending on the window size initially set and the max iterations set, the window will be updated in less than a second or in a couple of seconds to show the slected complex plane region of the Mandelbrot set

## Debugging

It is possible that you might run into this error 

`undefined reference to symbol 'pthread_create@@GLIBC_2.2.5'`,

When this happens, remove the `-std=c++17` flag from **CMakeLists.txt** file and run `make` again. This should solve the strange error.

## Run Parameters

1. kScreenDim - Display window dimension (the bigger this value is the more computations and hence possible to see some delay)
2. maxIter - Maximum number of iterations to check if the points on complex plane cross the 2.0 threshold
3. MandelbrotSetOrder - Determines the Mandelbrot set order to compute ` z = std::pow(z, SET_ORDER) + c`

## Rubric Points satisfied

- [x] A README with instructions is included with the project
- [x] The README indicates which project is chosen
- [x] The README includes information about each rubric point addressed
- [x] The submission must compile and run
- [x] The project demonstrates an understanding of C++ functions and control structures
- [x] The project accepts user input and processes the input
- [x] The project uses Object Oriented Programming techniques
- [x] Classes use appropriate access specifiers for class members
- [x] Class constructors utilize member initialization lists
- [x] Classes encapsulate behavior
- [x] Overloaded functions allow the same function to operate on different parameters
- [x] Templates generalize functions in the project
- [x] The project makes use of references in function declarations
- [x] The project uses destructors appropriately
- [x] The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate
- [x] The project uses shared pointer for a vector of tuples holding the color of each pixel
- [x] The project uses multiple threading to speed up the computations

## Credits

Some of the core computing functions are adopted from this article https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/