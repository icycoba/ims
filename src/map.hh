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

        // Methods
        void print_map();
        };
