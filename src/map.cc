/**
 * @file map.cc
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Zdrojový soubor mapy pro simulaci praskliny
 * @version 0.1
 * @date 2022-11-30
 */

#include "map.hh"
#include <iostream>

#include <SDL2/SDL.h>

void run_window(SDL_Window *window) {
    
}

void sdl_window_create(){
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO)<0){
        cout << "Could not initialize video: " << SDL_GetError() << endl;
    }
    else
    {
        window = SDL_CreateWindow(
            "CrackSim ;)))",
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            1000, 
            700, 
            SDL_WINDOW_SHOWN
        );
        if (window == NULL){
            cout << "Could not create window: " << SDL_GetError() << endl;
        }
        else
        {
            run_window(window);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Map::Map(){
    this->width = 100;
    this->height = 100;
}

Map::Map(unsigned int width, unsigned int height){
    this->width = width;
    this->height = height;
}

Map::~Map(){

}

unsigned int Map::get_width(){
    return this->width;
}

unsigned int Map::get_height(){
    return this->height;
}

std::vector<std::vector<Cell>> Map::get_cells(){
    return this->cells;
}

void Map::set_width(unsigned int width){
    this->width = width;
}

void Map::set_height(unsigned int height){
    this->height = height;
}

void Map::print_map(int *argc, char **argv)
{
    sdl_window_create();
}
