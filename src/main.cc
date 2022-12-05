/**
 * @file main.cc
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Zdrojový soubor, hlavní tělo programu
 * @version 0.1
 * @date 2022-11-30
 */

#include "main.hh"

#include <getopt.h>
#define HELP \
    "Usage:" << endl\
    << "./cracksim [-t mat_tolerance] [-e el_percentage]" << endl\
    << "Options:" << endl\
    << "-t\tMaterial tolerance. This value will affect the overal distribution of stress fields in material."\
    << endl << "\tDefault value is 14." << endl\
    << "-e\tMaterial elasticity percetnage. This value will affect Crack Module potential. Default value is 20." << endl
int main(int argc, char **argv){

    srand(time(nullptr));
    int c;

    while ((c = getopt_long(argc, argv, "t:e:h", NULL, NULL)) != -1){
        switch (c)
        {
        case 'h':
            cout << HELP;
            exit(0);
        case 't':
            MATERIAL_TOLERANCE = atoi(optarg);

            if (MATERIAL_TOLERANCE < 0)
            {
                cout << "Material tolerance should be greater then 0. Default value of 14 is used." << endl;
                cout << "For help message run with -h flag." << endl;
                MATERIAL_TOLERANCE = 14;
            }
            break;
        case 'e':
            MATERIAL_ELASTICITY_PERCENTAGE = atoi(optarg) / 100.0;
            if (MATERIAL_ELASTICITY_PERCENTAGE > 1 || MATERIAL_ELASTICITY_PERCENTAGE < 0)
            {
                cout << "Elasticity percentage should be between 0 and 100. Default value of 20 is used." << endl;
                cout << "For help message run with -h flag." << endl;
                MATERIAL_ELASTICITY_PERCENTAGE = 0.2;
            }
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            break;
        case ':':
            printf("Missing argument for -%c\n flag.", optopt);
            break;
        default:
            abort();
        }
    }
    Window gui = Window();
    gui.run_window();
    return 0;
}

