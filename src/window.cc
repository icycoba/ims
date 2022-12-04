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

Uint32 *Window::get_pixel(int x, int y)
{
	SDL_Surface *surface = this->get_surf();
	// this was find on the internet, i have no idea how it works but it does
	return (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
}

void Window::set_pixel(int x, int y, Uint32 color)
{
	Uint32 *const target_pixel = this->get_pixel(x, y);
	*target_pixel = color;
}

void Window::generate_starting_points()
{
	// prasácký statický int, aby se nám nezacyklil randomizer
	static int i = 0;
	// prasácký cyklus, který vygeneruje random 10 bodů, kde začínají praskliny
	for (; i < 10; i++)
	{
		int x = rand() % W_WIDTH;
		int y = rand() % W_HEIGHT;
		set_pixel( x, y, WHITE);
		cout << "x: " << x << " y: " << y << endl;
	}
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

	// for (size_t i=0; i<unstable.size(); i++)
	// {
	//     // "first" and "second" are used to access
	//     // 1st and 2nd element of pair respectively
	//     cout << unstable[i].first << " " << unstable[i].second << endl;
	// }

	while (is_running)
	{
		// this->generate_starting_points();
		while (SDL_PollEvent(&(this->ev)) != 0)
		{
			if (ev.type == SDL_QUIT)
				is_running = false;
			else if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				// Todo do we even want to make it crack on click? No we dont
				set_pixel(x, y, WHITE);
			}
		}
		this->map->apply_rule(this->get_surf());
		SDL_UpdateWindowSurface(window);
	}
}