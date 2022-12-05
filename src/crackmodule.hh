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
    public:
        CrackModule(int x, int y, double kineticPotential, Direction direction);
        ~CrackModule();

        int get_x();
        int get_y();
        double get_kinetic_potential();
        pair<int, int> get_direction();
        Direction get_direction_enum();

        void set_kinetic_potential(double kineticPotential);
        void set_direction(pair<int, int> direction);
        void set_direction_enum(Direction direction);
};