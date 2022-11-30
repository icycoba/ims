/**
 * @file main.hh
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Hlavičkový soubor buňky pro simulaci praskliny
 * @version 0.1
 * @date 2022-11-30
 */

class Cell{
    private:
        // Cell coordinates
        int x;
        int y;

        // Cell state
        int state;
    public:
        // Constructor/destructor
        Cell();
        ~Cell();

        // Getters
        int get_x();
        int get_y();
        int get_state();

        // Setters
        void set_x(int x);
        void set_y(int y);
        void set_state(int state);
};
