#include <thread>
#include <cmath>
#include "../include/display.h"

using std::size_t;

void Display::Run(Renderer &renderer){
	std::complex<double> tmp1, tmp2;
	std::vector<std::thread> threads;
	std::vector<std::tuple<size_t, size_t>> grid_pts;
	size_t n_cores = std::thread::hardware_concurrency();

	// disable out of window mouse activity capture
	SDL_CaptureMouse(SDL_FALSE);

	// to capture quit
	SDL_Event e;
	// zoom rectangle start and end points
	SDL_Point start, end;

	start.x = 0;
	start.y = 0;
	end.x = scr.x_max;
	end.y = scr.y_max;

	bool event = false;
	bool quit = false;
	bool first_run = true;

	size_t sub_domain_x, sub_domain_y;

  while (!quit){
		// loop exit
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT) {
      quit = true;
			continue;
    }
		// handle zoom
		SDL_PumpEvents();
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			if (!event){
				SDL_GetMouseState(&start.x, &start.y);
				event = true;
			}
			else{
				// update until event ends
				SDL_GetMouseState(&end.x, &end.y);
			}
		}
		// after an event or upon first run
		if (event & (!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))) | first_run ) {
			int width = end.x - start.x;
			int height = end.y - start.y;
			int square_side = std::max(width, height);
			
			if (!first_run) {
				tmp1 = fullDomainScale(std::complex<double>(start.x, start.y));
				tmp2 = fullDomainScale(std::complex<double>(start.x + square_side, start.y + square_side));
				
				fract.x_min = tmp1.real();
				fract.y_min = tmp1.imag();

				
				fract.x_max = tmp2.real();
				fract.y_max = tmp2.imag();
			}

			// unit is numbers on complex plane
			double fract_domain_width = (fract.x_max - fract.x_min) / (n_cores / 2);
			double fract_domain_height = (fract.y_max - fract.y_min) / 2;

			if (first_run) {
				// unit is pixels
				sub_domain_x = std::round(square_side / (n_cores / 2)); // appropriate number of columns
				sub_domain_y = std::round(square_side / 2); // 2 rows
        // create subdomain x and y coordinates
				for (int j = 0; j <= (n_cores / 2); j++){ // along x
					for (int i = 0; i <= 2; i++){ // along y
						grid_pts.emplace_back(std::tuple<int, int>(start.x + j * sub_domain_x, start.y + i * sub_domain_y));
					}
				}
			}

			threads.erase(threads.begin(), threads.end());
			for (int i = 0; i< n_cores; i++){
				// enables utilisation of pattern to pair diagonal coordinate pairs, top left to bottom right
				int tmp_idx = (i%2) + std::round(i/2)*3; 
				threads.emplace_back(std::thread(&Display::Mandelbrot, this,
				std::get<0>(grid_pts[tmp_idx]),
				std::get<1>(grid_pts[tmp_idx]),
				std::get<0>(grid_pts[tmp_idx + 4]),
				std::get<1>(grid_pts[tmp_idx + 4]),
				sub_domain_x, sub_domain_y, n_cores, 
				colors, i));
			}

			for (std::thread &t: threads){
				t.join();
			}

			renderer.Render(colors);

			event = false;
			first_run = false;
		}
	}
}

void Display::Mandelbrot(size_t xMin, size_t yMin, size_t xMax, size_t yMax,
												size_t sub_domain_width, size_t sub_domain_height, size_t cores, 
												std::shared_ptr<std::vector<std::tuple<size_t, size_t, size_t>>> clrs, size_t domain_no) 
{
	// Loop over each pixel from our image and check if the point associated with this pixel escapes to infinity
	int offset = std::round(domain_no / 2) * (2 * sub_domain_height) * sub_domain_width;
	int column = 0;
	for(int i = xMin; i < xMax; ++i) {
		for(int j = yMin; j < yMax; ++j) {
			std::complex<double> c((double)i, (double)j);
			c = scale(c, sub_domain_width, sub_domain_height, cores);
			/* sub-domain numbering, column first
			 * 0 2 4  
			 * 
			 * 1 3 5
			*/
			if (domain_no < 2) {
				map_color(c, j + column * 2 * sub_domain_height, clrs);
			}
			else {
				map_color(c, offset + j + column * 2 * sub_domain_height, clrs);
			}
		}
		column++;
	}
}

// Convert a pixel coordinate to the complex domain
std::complex<double> Display::fullDomainScale(std::complex<double> c) {
	std::complex<double> aux(c.real() / (double)scr.getWidth() * fract.getWidth() + fract.x_min,
		c.imag() / (double)scr.getHeight() * fract.getHeight() + fract.y_min);
	return aux;
}

// Convert a pixel coordinate to the complex domain, subdomain level
std::complex<double> Display::scale(std::complex<double> c, size_t &scr_x_max, size_t &scr_y_max, size_t n_cores) {
	std::complex<double> aux(c.real() / (double)scr_x_max * (fract.getWidth() / (n_cores / 2)) + fract.x_min,
		c.imag() / (double)scr_y_max * (fract.getHeight() / 2) + fract.y_min);
	return aux;
}

// Check if a point is in the set or escapes to infinity, return the number if iterations
void Display::map_color(std::complex<double> c, size_t &&idx, std::shared_ptr<std::vector<std::tuple<size_t, size_t, size_t>>> &clr) 
{
	std::complex<double> z(0);
	size_t iter = 0;

	while (abs(z) < 2.0 && iter < MAX_ITERS) {
		z = std::pow(z, SET_ORDER) + c;
		iter++;
	}
	set_color(iter, idx, clr);
}

void Display::set_color(size_t iter, size_t idx, std::shared_ptr<std::vector<std::tuple<size_t, size_t, size_t>>> &clr) {
	// map n on the 0..1 interval
	double t = (double)iter/(double)MAX_ITERS;

	// Use smooth polynomials for r, g, b
	int r = (int)(9*(1-t)*t*t*t*255);
	int g = (int)(15*(1-t)*(1-t)*t*t*255);
	int b =  (int)(8.5*(1-t)*(1-t)*(1-t)*t*255);
	
	std::get<0>((*clr)[idx]) = r;
	std::get<1>((*clr)[idx]) = g;
	std::get<2>((*clr)[idx]) = b;
}