/**
 * @file map.hh
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Hlavičkový soubor mapy pro simulaci praskliny
 * @version 0.1
 * @date 2022-11-30
 */

#include "cell.hh"

#include <iostream>
#include <ctime>
#include <unordered_map>

#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>

#define W_WIDTH 1000
#define W_HEIGHT 720

struct neighbourhood
{
    bool top_left = false;
    bool top = false;
    bool top_right = false;
    bool left = false;
    bool bottom_left = false;
    bool bottom = false;
    bool bottom_right = false;
    bool right = false;
};

class Map{
    private:
        // Map parameters
        unsigned int width;
        unsigned int height;

        // Map material
        int elasticityLoop;
        float elasticitySharing;

        // Map cells
        Cell *** cells;
        Cell *** next_cells;

    public:
        // Constructor/destructor
        Map(unsigned int width, unsigned int height);
        ~Map();

        // Getters
        unsigned int get_width();
        unsigned int get_height();
        Cell *** get_cells();
        Cell get_cell(int x, int y);

        // Setters
        void set_width(unsigned int width);
        void set_height(unsigned int height);
        void copy_cells(Cell *** src, Cell *** dst);
        Cell *** allocate_cells();
        void free_cells(Cell *** cells);
        void stress_relaxation();

        // Methods
        void print_map();

        neighbourhood create_moore(int x, int y);
        void apply_rule(neighbourhood n, SDL_Surface *new_surface, int x, int y);
        void scan_window(SDL_Surface *old_surface);
        void generate_starting_points(SDL_Surface *window_surf);
        vector<pair<Cell*, double>> set_unstable();
        void run_window(SDL_Window *window);
        void sdl_window_create();

        unordered_map<string, Cell*> get_neigh(int x, int y);
        };
