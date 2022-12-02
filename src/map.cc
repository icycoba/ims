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


#define WHITE 0xffffffff
#define RED 0xff0000ff

Uint32 *get_pixel(SDL_Surface *surface, int x, int y)
{
    return (Uint32 *)((Uint8 *)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
}

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint32 *const target_pixel = get_pixel(surface, x, y);
    *target_pixel = pixel;
}

bool is_set(Uint32 *pixel)
{
    return *pixel == WHITE;
}

void run_window(SDL_Window *window) {
    
    bool is_running = true;

    SDL_Surface *window_surf = SDL_GetWindowSurface(window);
    SDL_Surface *new_surf = SDL_CreateRGBSurface(0, window_surf->w, window_surf->h, 32, 0, 0, 0, 0);
    SDL_Event ev;

    while (is_running)
    {
        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_QUIT)
                is_running = false;
            else if (ev.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                cout << "x: " << x << "\t y: " << y << endl;
                set_pixel(window_surf, x, y, WHITE);
            }
        }
        SDL_UpdateWindowSurface(window);
        //SDL_Delay(1000);
    }

    SDL_FreeSurface(window_surf);
    SDL_FreeSurface(new_surf);
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
