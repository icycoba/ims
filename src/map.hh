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

        void copy_cells(Cell *** src, Cell *** dst);
        Cell *** allocate_cells();
        void free_cells(Cell *** cells);
        void stress_relaxation();

        // Methods
        void apply_rule(SDL_Surface *new_surface);

        vector<pair<Cell*, double>> set_unstable();

        unordered_map<string, Cell*> get_neigh(int x, int y);
};