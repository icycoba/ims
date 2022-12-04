#include "map.hh"

#define W_WIDTH 1000
#define W_HEIGHT 720

#define TOP x, y - 1
#define TOP_RIGHT x + 1, y - 1
#define TOP_LEFT x - 1, y - 1
#define BOTTOM x, y + 1
#define BOTTOM_RIGHT x + 1, y + 1
#define BOTTOM_LEFT x - 1, y + 1
#define RIGHT x + 1, y
#define LEFT x - 1, y

class Window
{
private:
	SDL_Window *window;
	SDL_Surface *surface;
	SDL_Event ev;
	Map *map;

public:
	Window();
	~Window();
	SDL_Surface *get_surf();
	void generate_starting_points();
	void run_window();
};

