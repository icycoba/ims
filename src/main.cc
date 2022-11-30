/**
 * @file main.hh
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Zdrojový soubor, hlavní tělo programu
 * @version 0.1
 * @date 2022-11-30
 */

#include "main.hh"

int main(int argc, char **argv){
    std::vector <std::string> args(argv, argv+argc);
    if(args.size() > 1){
        for(std::string arg : args){
            std::cout << arg << std::endl;
        }
    } else{
        //TODO - implement help print
        std::cout << "No arguments, printing help TODO" << std::endl;
    }
    return 0;
}