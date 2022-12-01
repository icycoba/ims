/**
 * @file main.hh
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Hlavičkový soubor mapy pro simulaci praskliny
 * @version 0.1
 * @date 2022-11-30
 */

#include "cell.hh"

#include <vector>

enum class MaterialType{
    Mud,
    Concrete,
    Glaze,
    Ceramic,
    Glass,
    Stone,
    Metal,
    Wood,
    Ice
};

class Map{
    private:
        // Map parameters
        // Should it be unsigned? Will it even be necessary? TODO -xhlins01
        unsigned int width;
        unsigned int height;

        // Map material
        int elasticityLoop;
        float elasticitySharing;

        // Map cells
        std::vector<std::vector<Cell>> cells;
    public:
        // Constructor/destructor
        Map();
        Map(unsigned int width, unsigned int height);
        ~Map();

        // Getters
        int get_width();
        int get_height();
        std::vector<std::vector<Cell>> get_cells();
        Cell get_cell(int x, int y);

        // Setters
        void set_width(int width);
        void set_height(int height);
        void set_cells(std::vector<std::vector<Cell>> cells);

        // Methods
        void print_map();
};