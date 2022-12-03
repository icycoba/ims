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
#include <ctime>

#include <SDL2/SDL.h>

struct neighbourhood
{
    bool top_left = false;
    bool top = false;
    bool top_right = false;
    bool left = false;
    bool bottom_left = false;
    bool bottom = false;
    bool bottom_right = false;
    bool right = false;
};

#define WHITE 0xffffffff
#define RED 0xff0000ff

#define TOP x, y - 1
#define TOP_RIGHT x + 1, y - 1
#define TOP_LEFT x - 1, y - 1
#define BOTTOM x, y + 1
#define BOTTOM_RIGHT x + 1, y + 1
#define BOTTOM_LEFT x - 1, y + 1
#define RIGHT x + 1, y
#define LEFT x - 1, y

Uint32 *get_pixel(SDL_Surface *surface, int x, int y)
{
    // this was find on the internet, i have no idea how it works but it does
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

neighbourhood create_moore(SDL_Surface *surface, int x, int y)
{
    neighbourhood result;
    result.top          = is_set(get_pixel(surface, TOP));
    result.top_right    = is_set(get_pixel(surface, TOP_RIGHT));
    result.top_left     = is_set(get_pixel(surface, TOP_LEFT));
    result.right        = is_set(get_pixel(surface, RIGHT));
    result.bottom_right = is_set(get_pixel(surface, BOTTOM_RIGHT));
    result.bottom       = is_set(get_pixel(surface, BOTTOM));
    result.bottom_left  = is_set(get_pixel(surface, BOTTOM_LEFT));
    result.left         = is_set(get_pixel(surface, LEFT));
    return result;
}

void apply_rule(neighbourhood n, SDL_Surface *new_surface, int x, int y)
{
    if(n.top_right || n.bottom_right || n.bottom_left || n.top_left){
        if (n.top_right && ! n.bottom_left){
            set_pixel(new_surface, BOTTOM_LEFT, WHITE);
        }
        if (n.top_left && !n.bottom_right)
        {
            set_pixel(new_surface, BOTTOM_RIGHT, WHITE);
        }

        if (!n.top_left && n.bottom_right)
        {
            set_pixel(new_surface, TOP_LEFT, WHITE);
        }
        if (!n.top_right && n.bottom_left)
        {
            set_pixel(new_surface, TOP_RIGHT, WHITE);
        }
    }
    else{
        set_pixel(new_surface, TOP_LEFT, WHITE);
        set_pixel(new_surface, TOP_RIGHT, WHITE);
        set_pixel(new_surface, BOTTOM_RIGHT, WHITE);
        set_pixel(new_surface, BOTTOM_LEFT, WHITE);
    }
}

void scan_window(SDL_Surface *old_surface, SDL_Surface *new_surface)
{
    if (old_surface == NULL){
        cerr << "DumB" << endl;
        return;
    }
    SDL_BlitSurface(old_surface, NULL, new_surface, NULL);
    if (new_surface == NULL){
        cerr << "dumb" << endl;
        return;
    }
    int w_max = (old_surface->w) - 1;
    int h_max = (old_surface->h) - 1;
    for (int x = 1; x < w_max; x++)
    {
        for (int y = 1; y < h_max; y++){
            if (is_set(get_pixel(old_surface, x, y))){
                neighbourhood moore = create_moore(old_surface, x, y);
                apply_rule(moore, new_surface, x, y);
            }
        }
    }
}

void generate_starting_points(SDL_Surface *window_surf){
    // prasácký statický int, aby se nám nezacyklil randomizer
    static int i = 0;
    // prasácký cyklus, který vygeneruje random 10 bodů, kde začínají praskliny
    for (; i < 10; i++)
    {
        int x = rand() % window_surf->w;
        int y = rand() % window_surf->h;
        set_pixel(window_surf, x, y, WHITE);
        cout << "x: " << x << " y: " << y << endl;
    }
}

void run_window(SDL_Window *window) {
    
    bool is_running = true;

    SDL_Surface *window_surf = SDL_GetWindowSurface(window);
    SDL_Surface *new_surf = SDL_CreateRGBSurface(0, window_surf->w, window_surf->h, 32, 0, 0, 0, 0);
    SDL_Event ev;

    while (is_running)
    {
        generate_starting_points(window_surf);
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
        scan_window(window_surf, new_surf);
        SDL_BlitSurface(new_surf, NULL, window_surf, NULL);
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

Map::Map(unsigned int width, unsigned int height){
    this->width = width;
    this->height = height;

    this->cells = allocate_cells();

    this->next_cells = allocate_cells();
    this->copy_cells(this->cells, this->next_cells);
}

Map::~Map(){
    this->free_cells(this->cells);
    this->free_cells(this->next_cells);
}

unsigned int Map::get_width(){
    return this->width;
}

unsigned int Map::get_height(){
    return this->height;
}

Cell *** Map::get_cells(){
    return this->cells;
}

void Map::set_width(unsigned int width){
    this->width = width;
}

void Map::set_height(unsigned int height){
    this->height = height;
}

void Map::print_map()
{
    sdl_window_create();
}

Cell *** Map::allocate_cells()
{
    Cell *** result = new Cell **[this->height];

    for (unsigned int i = 0; i < this->height; i++)
    {
        Cell **row = new Cell*[this->width];
        result[i] = row;
        for (unsigned int j = 0; j < this->width; j++)
        {
            result[i][j] = new Cell(i, j);
        }
    }
    return result;
}

void Map::free_cells(Cell ***cells)
{
    for (unsigned int i = 0; i < this->height; i++)
    {
        for (unsigned int j = 0; j < this->width; j++)
        {
            delete cells[i][j];
        }
        delete cells[i];
    }
    delete cells;
}

void Map::copy_cells(Cell *** src, Cell *** dst)
{
    for (unsigned int i = 0; i < this->height; i++)
    {
        for (unsigned int j = 0; j < this->width; j++)
        {
            *dst[i][j] = *src[i][j];
        }
    }
}