#include "window.hh"

Window::Window()
{
	this->map = new Map(W_WIDTH, W_HEIGHT);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Could not initialize video: " << SDL_GetError() << endl;
		exit(1);
	}
	else
	{
		this->window = SDL_CreateWindow(
			"CrackSim ;(",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W_WIDTH,
			W_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "Could not create window: " << SDL_GetError() << endl;
			exit(1);
		}
	}
	this->surface = SDL_GetWindowSurface(this->window);
}

Window::~Window()
{
	delete this->map;
	SDL_FreeSurface(this->surface);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

SDL_Surface *Window::get_surf(){
	return SDL_GetWindowSurface(this->window);
}

#include <algorithm>
bool sortbysec(const pair<Cell *, double> &a, const pair<Cell *, double> &b)
{
	return (a.second > b.second);
}

void Window::run_window()
{

	bool is_running = true;

	vector<pair<Cell *, double>> unstable = this->map->set_unstable();
	sort(unstable.begin(), unstable.end(), sortbysec);
	this->map->apply_rule(this->get_surf(), unstable);

	while (is_running)
	{
		while (SDL_PollEvent(&(this->ev)) != 0)
		{
			if (ev.type == SDL_QUIT)
				is_running = false;
		}	
		SDL_UpdateWindowSurface(window);
	}
}