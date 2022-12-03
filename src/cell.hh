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

using namespace std;

#define MATERIAL_TOLERANCE 14
#define MATERIAL_ELASTICITY_LOOP 5
#define MATERIAL_ELASTICITY_SHARING 0.1

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
        int x;
        int y;

        // Cell state
        CellState state; // Intact, Cracked

        // Cell stress spectrum
        vector<double> stressSpectrum; // (RIGHT, TOP_RIGHT, TOP, TOP_LEFT). Values are mirrored in the opposite direction
    public:
        // Constructor/destructor
        Cell();
        Cell(unsigned int i, unsigned int j, vector<double> stressSpectrum);
        ~Cell();

        // Getters
        pair<int, int> get_coordinates();
        CellState get_state();
        vector<double> get_stress_spectrum();

        // Setters
        void set_coordinates(int x, int y);
        void set_state(CellState state);
};
