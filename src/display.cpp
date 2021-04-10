#include "../include/display.h"
#include <cmath>

void Display::Run(Renderer &renderer){
	std::complex<double> tmp1, tmp2;
  Mandelbrot(renderer);
	renderer.Render(colors);
	int width;
	int height;
	// disable capturing mouse events outside the window
	SDL_CaptureMouse(SDL_FALSE);

	SDL_Event e;
	SDL_Point start, end;
	bool event = false;
	bool quit = false;
  while (!quit){
		// loop exit
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
      quit = true;
			continue;
    }
		// zoom functionality
		SDL_PumpEvents();
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			if (!event){
				SDL_GetMouseState(&start.x, &start.y);
				event = true;
			}
			else{
				SDL_GetMouseState(&end.x, &end.y); // keep overwriting till the end of the event
			}
		}
		// after a zoom event
		if (event & (!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)))) {
			tmp1 = scale(std::complex<double>(start.x, start.y));
			
			height = end.y - start.y;
			width = end.x - start.x;

			tmp2 = scale(std::complex<double>(start.x + std::max(width, height), start.y + std::max(width, height)));
			
			fract.x_min = tmp1.real();
			fract.y_min = tmp1.imag();

			fract.x_max = tmp2.real();
			fract.y_max = tmp2.imag();
			


			colors.clear();
			Mandelbrot(renderer);
			renderer.Render(colors);

			event = false;
		}
	}
}

void Display::Mandelbrot(Renderer &renderer) 
{
	calculate_number_iterations();
}

// Loop over each pixel from our image and check if the point associated with this pixel escapes to infinity
void Display::calculate_number_iterations() {
	for(int i = scr.y_min; i < scr.y_max; ++i) {
		for(int j = scr.x_min; j < scr.x_max; ++j) {
			std::complex<double> c((double)j, (double)i);
			c = scale(c);
			map_color(c);
		}
	}
}

// Convert a pixel coordinate to the complex domain
std::complex<double> Display::scale(std::complex<double> c) {
	std::complex<double> aux(c.real() / (double)scr.getWidth() * fract.getWidth() + fract.x_min,
		c.imag() / (double)scr.getHeight() * fract.getHeight() + fract.y_min);
	return aux;
}


// Check if a point is in the set or escapes to infinity, return the number if iterations
void Display::map_color(std::complex<double> c) 
{
	std::complex<double> z(0);
	int iter = 0;

	while (abs(z) < 2.0 && iter < MAX_ITERS) {
		z = std::pow(z, SET_ORDER) + c;
		iter++;
	}
	set_color(iter);
}

void Display::set_color(int iter) {
	// map n on the 0..1 interval
	double t = (double)iter/(double)MAX_ITERS;

	// Use smooth polynomials for r, g, b
	int r = (int)(9*(1-t)*t*t*t*255);
	int g = (int)(15*(1-t)*(1-t)*t*t*255);
	int b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
	colors.emplace_back(std::tuple(r, g, b));
}