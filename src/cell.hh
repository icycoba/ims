/**
 * @file cell.hh
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Hlavičkový soubor buňky pro simulaci praskliny
 * @version 0.1
 * @date 2022-11-30
 */

#include <vector>
#include <random>

#define WHITE 0xffffffff
#define RED 0x00ffffff

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

using namespace std;

#define MATERIAL_TOLERANCE 14
#define MATERIAL_ELASTICITY_LOOP 5
#define MATERIAL_ELASTICITY_SHARING 0.1
#define MATERIAL_ELASTICITY_PERCENTAGE 0.2

/**
 * @brief Stav buňky
 */
enum class CellState{
    Default, 
    Intact, // Crack not ran through by crack
    Cracked // Crack runs through the cell
};

class Cell{
    private:
        // Cell coordinates
        uint x;
        uint y;

        // Cell state
        CellState state; // Intact, Cracked

        // Cell stress spectrum
        vector<double> stressSpectrum; // (RIGHT, TOP_RIGHT, TOP, TOP_LEFT). Values are mirrored in the opposite direction
    public:
        // Constructor/destructor
        Cell();
        Cell(uint i, uint j, vector<double> stressSpectrum);
        ~Cell();

        // Getters
        pair<uint, uint> get_coordinates();
        CellState get_state();
        vector<double> get_stress_spectrum();
        double get_stress_avg();

        Uint32 *get_pixel(SDL_Surface *surface);


        // Setters
        void set_coordinates(uint x, uint y);
        void set_state(CellState state);
        void set_stress_spectrum(vector<double> stressSpectrum);

        void set_pixel(SDL_Surface *surface, Uint32 color);
        // Methods
        uint maximum_stress();
};
