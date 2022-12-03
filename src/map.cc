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




neighbourhood Map::create_moore(SDL_Surface *surface, int x, int y)
{
    neighbourhood result;
    
    Cell *** cells = this->get_cells();
    //cells[x][y]->set_state(CellState::Intact);
    if(cells == nullptr){
        cerr << "cells is null" << endl;
    }

    if(cells[x] == nullptr){
        cerr << "cells[x] is null" << endl;
        cerr << "x: " << x << endl;
    }

    if(cells[x][y] == nullptr){
        cerr << "cells[x][y] is null" << endl;
        cerr << "x: " << x << " y: " << y << endl;
    }
    //cout << (cells[216][125]->get_state() == CellState::Default) << endl;

    //cout << "x: " << x << " y: " << y << endl;
    //cout << (cells[x/8][y/8]->get_state() == CellState::Default) << endl;

    // result.top              = map->get_cells()[(x)/8][(y-1)/8]->get_state() == CellState::Default;
    // result.top_right        = map->get_cells()[(x+1)/8][(y-1)/8]->get_state() == CellState::Default;
    // result.top_left         = map->get_cells()[(x-1)/8][(y-1)/8]->get_state() == CellState::Default;
    // result.right            = map->get_cells()[(x+1)/8][(y)/8]->get_state() == CellState::Default;
    // result.bottom_right     = map->get_cells()[(x+1)/8][(y+1)/8]->get_state() == CellState::Default;
    // result.bottom           = map->get_cells()[(x)/8][(y+1)/8]->get_state() == CellState::Default;
    // result.bottom_left      = map->get_cells()[(x-1)/8][(y+1)/8]->get_state() == CellState::Default;
    // result.left             = map->get_cells()[(x-1)/8][(y)/8]->get_state() == CellState::Default;
    
    result.top          = is_set(get_pixel(surface, TOP));
    result.top_right    = is_set(get_pixel(surface, TOP_RIGHT));
    result.top_left     = is_set(get_pixel(surface, TOP_LEFT));
    result.right        = is_set(get_pixel(surface, RIGHT));
    result.bottom_right = is_set(get_pixel(surface, BOTTOM_RIGHT));
    result.bottom       = is_set(get_pixel(surface, BOTTOM));
    result.bottom_left  = is_set(get_pixel(surface, BOTTOM_LEFT));
    result.left         = is_set(get_pixel(surface, LEFT));


    // if(map->get_cells()[x/8][y/8]->get_state() == CellState::Cracked){
    //     cout << "dong" << endl;
    // } else {
    //     cout << "dang" << endl;
    // }


    //result.top          = map->get_cell(TOP).get_state() == CellState::Default;
    //result.top_right    = map->get_cell(TOP_RIGHT).get_state() == CellState::Default;
    //result.top_left     = map->get_cell(TOP_LEFT).get_state() == CellState::Default;
    //result.right        = map->get_cell(RIGHT).get_state() == CellState::Default;
    //result.bottom_right = map->get_cell(BOTTOM_RIGHT).get_state() == CellState::Default;
    //result.bottom       = map->get_cell(BOTTOM).get_state() == CellState::Default;
    //result.bottom_left  = map->get_cell(BOTTOM_LEFT).get_state() == CellState::Default;
    //result.left         = map->get_cell(LEFT).get_state() == CellState::Default;
    return result;
}

void Map::apply_rule(neighbourhood n, SDL_Surface *new_surface, int x, int y)
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

void Map::scan_window(SDL_Surface *old_surface, SDL_Surface *new_surface)
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
    int w_max = (this->width) - 1;
    int h_max = (this->height) - 1;
    cout << w_max << " " << h_max << endl;
    for (int x = 1; x < w_max; x++)
    {
        for (int y = 1; y < h_max; y++){
            Uint32 *pixel = get_pixel(old_surface, x, y);
            if(pixel != NULL){
                if (is_set(pixel)){
                    neighbourhood moore = this->create_moore(old_surface, x, y);
                    apply_rule(moore, new_surface, x, y);
                }
            } else{
                cerr << "pixel is null" << endl;
            }
        }
    }
}

void Map::generate_starting_points(SDL_Surface *window_surf){
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

void Map::run_window(SDL_Window *window) {
    
    bool is_running = true;

    SDL_Surface *window_surf = SDL_GetWindowSurface(window);
    SDL_Surface *new_surf = SDL_CreateRGBSurface(0, window_surf->w, window_surf->h, 32, 0, 0, 0, 0);
    SDL_Event ev;

    while (is_running)
    {
        //generate_starting_points(window_surf);
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
        this->scan_window(window_surf, new_surf);
        SDL_BlitSurface(new_surf, NULL, window_surf, NULL);
        SDL_UpdateWindowSurface(window);
        //SDL_Delay(1000);
    }

    SDL_FreeSurface(window_surf);
    SDL_FreeSurface(new_surf);
}

void Map::sdl_window_create(){
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO)<0){
        cout << "Could not initialize video: " << SDL_GetError() << endl;
    }
    else
    {
        window = SDL_CreateWindow(
            "CrackSim ;)))))))))))))))))))))))))))))))))))))))",
            SDL_WINDOWPOS_CENTERED, 
            SDL_WINDOWPOS_CENTERED, 
            W_WIDTH, 
            W_HEIGHT, 
            SDL_WINDOW_SHOWN
        );
        if (window == NULL){
            cout << "Could not create window: " << SDL_GetError() << endl;
        }
        else
        {
            this->run_window(window);
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

/*Cell Map::get_cell(int x, int y){
    cout << "xxx: " << x << " yyy: " << y << endl;
    return this->cells[x][y][0];
}*/

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
    // wight = 4
    // hght = 3
    
    ////
    ////
    ////
    default_random_engine generator;
    normal_distribution<double> distribution(MATERIAL_TOLERANCE / 2, (MATERIAL_TOLERANCE / 4) + 2 );

    Cell *** result = new Cell **[this->width];

    for (unsigned int i = 0; i < this->width; i++)
    {
        Cell **row = new Cell*[this->height];
        result[i] = row;
        for (unsigned int j = 0; j < this->height; j++)
        {
            //int ssindex = 0;
            
            result[i][j] = new Cell(i, j, {abs(distribution(generator)), abs(distribution(generator)), abs(distribution(generator)), abs(distribution(generator))});
            //for (double stressSpectrum : result[i][j][0].get_stress_spectrum()){
            //    cout << ssindex << ": " << stressSpectrum << endl;
            //    ssindex++;
            //}
            //cout << (result[j][i]->get_state() == CellState::Default) << endl;
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
    for (unsigned int i = 0; i < this->width; i++)
    {
        for (unsigned int j = 0; j < this->height; j++)
        {
            *dst[i][j] = *src[i][j];
        }
    }
}