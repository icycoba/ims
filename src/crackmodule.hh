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
        uint x;
        uint y;

        double kineticPotential;
        pair<uint, uint> direction;
        Direction directionEnum;
    public:
        CrackModule(uint x, uint y, double kineticPotential, Direction direction);
        ~CrackModule();

        uint get_x();
        uint get_y();
        double get_kinetic_potential();
        pair<uint, uint> get_direction();
        Direction get_direction_enum();

        void set_kinetic_potential(double kineticPotential);
        void set_direction(pair<uint, uint> direction);
        void set_direction_enum(Direction direction);
};