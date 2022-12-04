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

class CrackModule{
    private:
        int x;
        int y;

        double kineticPotential;
    public:
        CrackModule(int x, int y, double kineticPotential);
        ~CrackModule();

        int get_x();
        int get_y();
        double get_kinetic_potential();
        void set_kinetic_potential(double kineticPotential);
};