/**
 * @file crackmodule.hh
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Hlavičkový soubor konce praskliny
 * @version 0.1
 * @date 2022-11-30
 */

#include "cell.hh"

enum class Direction{
    TOP,
    TOP_RIGHT,
    RIGHT,
    BOTTOM_RIGHT,
    BOTTOM,
    BOTTOM_LEFT,
    LEFT,
    TOP_LEFT,
    NONE
};

class CrackModule{
    private:
        int x;
        int y;

        double kineticPotential;
        pair<int, int> direction;
        Direction directionEnum;
        void set_direction(Direction direction_enum);

    public:
        CrackModule(uint x, uint y, double kineticPotential);
        ~CrackModule();

        pair<int, int> get_coordinates();
        double get_kinetic_potential();
        Direction get_direction_enum();

        void set_kinetic_potential(double kineticPotential);
        
        void set_direction_enum(Direction direction);

        void move_in_direction();
};

Direction map_stress_field(uint index, bool head);
pair<int, int> map_direction(Direction direction_enum);