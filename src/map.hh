/**
 * @file map.hh
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Hlavičkový soubor mapy pro simulaci praskliny
 * @version 0.1
 * @date 2022-11-30
 */

#include "crackmodule.hh"

#include <iostream>
#include <ctime>
#include <unordered_map>

#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>

class Map{
    private:
        // Map parameters
        uint width;
        uint height;

        // Map material
        uint elasticityLoop;
        float elasticitySharing;

        // Map cells
        Cell *** cells;
        Cell *** next_cells;

    public:
        // Constructor/destructor
        Map(uint width, uint height);
        ~Map();

        // Getters
        uint get_width();
        uint get_height();
        Cell *** get_cells();
        Cell get_cell(uint x, uint y);

        void copy_cells(Cell *** src, Cell *** dst);
        Cell *** allocate_cells();
        void free_cells(Cell *** cells);
        void stress_relaxation();

        // Methods
        void apply_rule(SDL_Surface *new_surface, vector<pair<Cell *, double>> *unstable_list, vector<pair<CrackModule*, CrackModule*>*> *crack_list);

        void set_unstable(vector<pair<Cell *, double>> *unstable_list);

        unordered_map<string, Cell*> get_neigh(uint x, uint y);
};