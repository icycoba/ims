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
#include <algorithm> 

#define WHITE 0xffffffff
#define RED 0xffff0000

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

bool is_set_state(CellState state)
{
    return state == CellState::Cracked;
}

bool stress_gt_tolerance(vector<double> stress, int index){
    return stress[index] > MATERIAL_TOLERANCE - 4;

}

/*void random_rule(){
    Cell *** cells = this->get_cells();
    vector<double> stress = cells[x][y]->get_stress_spectrum();   

    if (stress_gt_tolerance(stress,0))
    {
        cells[x+1][y]->set_state(CellState::Cracked);
        cells[x-1][y]->set_state(CellState::Cracked);
    }
    if (stress_gt_tolerance(stress, 1))
    {
        cells[x+1][y-1]->set_state(CellState::Cracked);
        cells[x-1][y+1]->set_state(CellState::Cracked);
    }
    if (stress_gt_tolerance(stress, 2))
    {
        cells[x][y+1]->set_state(CellState::Cracked);
        cells[x][y-1]->set_state(CellState::Cracked);
    }
    if (stress_gt_tolerance(stress, 3))
    {
        cells[x+1][y+1]->set_state(CellState::Cracked);
        cells[x-1][y-1]->set_state(CellState::Cracked);
    }
}*/

neighbourhood Map::create_moore(int x, int y)
{
    neighbourhood result;
    
    /**DEBUG
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
    }*/
    // cout << is_set_state(CellState::Cracked) << endl;

    result.top              = is_set_state(cells[x][y-1]->get_state());
    result.top_right        = is_set_state(cells[x+1][y-1]->get_state());
    result.top_left         = is_set_state(cells[x-1][y-1]->get_state());
    result.right            = is_set_state(cells[x+1][y]->get_state());
    result.bottom_right     = is_set_state(cells[x+1][y+1]->get_state());
    result.bottom           = is_set_state(cells[x][y+1]->get_state());
    result.bottom_left      = is_set_state(cells[x-1][y+1]->get_state());
    result.left             = is_set_state(cells[x-1][y]->get_state());

    // cout << "top: " << result.top << endl;
    // cout << "top_right: " << result.top_right << endl;
    // cout << "top_left: " << result.top_left << endl;
    // cout << "right: " << result.right << endl;
    // cout << "bottom_right: " << result.bottom_right << endl;
    // cout << "bottom: " << result.bottom << endl;
    // cout << "bottom_left: " << result.bottom_left << endl;
    // cout << "left: " << result.left << endl;

    return result;
}

void Map::apply_rule(neighbourhood n, SDL_Surface *new_surface, int x, int y)
{
    //if(n.top_right || n.bottom_right || n.bottom_left || n.top_left){
    //    if (n.top_right && !n.bottom_left){
    //        set_pixel(new_surface, BOTTOM_LEFT, WHITE);
    //        this->next_cells[x-1][y+1]->set_state(CellState::Cracked);
    //    }
    //    if (n.top_left && !n.bottom_right)
    //    {
    //        set_pixel(new_surface, BOTTOM_RIGHT, WHITE);
    //        this->next_cells[x+1][y+1]->set_state(CellState::Cracked);
    //    }
    //
    //    if (!n.top_left && n.bottom_right)
    //    {
    //        set_pixel(new_surface, TOP_LEFT, WHITE);
    //        this->next_cells[x-1][y-1]->set_state(CellState::Cracked);
    //    }
    //    if (!n.top_right && n.bottom_left)
    //    {
    //        set_pixel(new_surface, TOP_RIGHT, WHITE);
    //        this->next_cells[x+1][y+1]->set_state(CellState::Cracked);
    //    }
    //}
    //else{
    //    set_pixel(new_surface, TOP_LEFT, WHITE);
    //    set_pixel(new_surface, TOP_RIGHT, WHITE);
    //    set_pixel(new_surface, BOTTOM_RIGHT, WHITE);
    //    set_pixel(new_surface, BOTTOM_LEFT, WHITE);
    //    
    //    this->next_cells[x-1][y-1]->set_state(CellState::Cracked);
    //    this->next_cells[x+1][y-1]->set_state(CellState::Cracked);
    //    this->next_cells[x-1][y+1]->set_state(CellState::Cracked);
    //    this->next_cells[x+1][y+1]->set_state(CellState::Cracked);
    //}
    
    if(n.top){
        set_pixel(new_surface, TOP, WHITE);
        //this->next_cells[x+1][y]->set_state(CellState::Cracked);
    }
    if(n.top_right){
        set_pixel(new_surface, TOP_RIGHT, WHITE);
        //this->next_cells[x+1][y-1]->set_state(CellState::Cracked);
    }
    if(n.right){
        set_pixel(new_surface, RIGHT, WHITE);
        //this->next_cells[x][y-1]->set_state(CellState::Cracked);
    }
    if(n.bottom_right){
        set_pixel(new_surface, BOTTOM_RIGHT, WHITE);
        //this->next_cells[x-1][y-1]->set_state(CellState::Cracked);
    }
    if(n.bottom){
        set_pixel(new_surface, BOTTOM, WHITE);
        //this->next_cells[x-1][y]->set_state(CellState::Cracked);
    }
    if(n.bottom_left){
        set_pixel(new_surface, BOTTOM_LEFT, WHITE);
        //this->next_cells[x-1][y+1]->set_state(CellState::Cracked);
    }
    if(n.left){
        set_pixel(new_surface, LEFT, WHITE);
        //this->next_cells[x][y+1]->set_state(CellState::Cracked);
    }
    if(n.top_left){
        set_pixel(new_surface, TOP_LEFT, WHITE);
        //this->next_cells[x+1][y+1]->set_state(CellState::Cracked);
    }
}

void Map::scan_window(SDL_Surface *old_surface)
{
    
    int w_max = (this->width) - 1;
    int h_max = (this->height) - 1;
    for (int x = 1; x < w_max; x++)
    {
        for (int y = 1; y < h_max; y++){
            Uint32 *pixel = get_pixel(old_surface, x, y);
            if(pixel != NULL){
                if (is_set(pixel)){
                    neighbourhood moore = this->create_moore(x, y);
                    apply_rule(moore, old_surface, x, y);
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

bool sortbysec(const pair<Cell*,double> &a, const pair<Cell*,double> &b)
{
    return (a.second > b.second);
}

vector<pair<Cell*, double>> Map::set_unstable(){
    vector<pair<Cell*, double>> result;
    for (unsigned int x = 0; x < this->width; x++)
    {
        for (unsigned int y = 0; y < this->height; y++)
        {
            if (this->cells[x][y]->get_state() != CellState::Cracked){
                int maxIndex = this->cells[x][y]->maximum_stress();
                double intensity = this->cells[x][y]->get_stress_spectrum()[maxIndex];
                if ( (int)intensity > MATERIAL_TOLERANCE){
                    result.push_back(pair<Cell*,double>(this->cells[x][y], intensity));
                }
            }
            
        }
    }
    return result;
}

// bool sortbysec(const pair<int,int> &a,
//     const pair<int,int> &b)
// {
//     return (a.second < b.second);
// }

void Map::run_window(SDL_Window *window) {
    
    bool is_running = true;

    SDL_Surface *window_surf = SDL_GetWindowSurface(window);
    SDL_Event ev;

    vector<pair<Cell*, double>> unstable = this->set_unstable();
    sort(unstable.begin(), unstable.end(), sortbysec);

    for (size_t i=0; i<unstable.size(); i++)
    {
        // "first" and "second" are used to access
        // 1st and 2nd element of pair respectively
        int x = unstable[i].first->get_coordinates().first;
        int y = unstable[i].first->get_coordinates().second;
        if(i==0){
            set_pixel(window_surf, x, y, WHITE);
        }
        else{
            set_pixel(window_surf, x, y, RED);
        }
        int maxIndex = unstable[i].first->maximum_stress();
        CrackModule cm = CrackModule(x, y, unstable[i].second);
    }
    
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

        this->scan_window(window_surf);
        SDL_UpdateWindowSurface(window);
        //SDL_Delay(1000);
    }

    SDL_FreeSurface(window_surf);
}

void Map::sdl_window_create(){
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO)<0){
        cout << "Could not initialize video: " << SDL_GetError() << endl;
    }
    else
    {
        window = SDL_CreateWindow(
            "CrackSim ;(",
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

void Map::stress_relaxation(){

    for(unsigned int x = 1; x < this->width-1; x++){
        for(unsigned int y = 1; y < this->height-1; y++){
            
            vector<double> sigma = {0, 0, 0, 0};
            double my_stress = this->cells[x][y]->get_stress_avg();
            vector<double> stress_sum = {0,0,0,0};

            unordered_map<string, Cell*> neighs = this->get_neigh(x,y);
            int infNeighbours = 0;

            for( const pair<const string, Cell*>& n : neighs){
                if(my_stress > n.second->get_stress_avg()){
                    stress_sum[0] += n.second->get_stress_spectrum()[0];
                    stress_sum[1] += n.second->get_stress_spectrum()[1];
                    stress_sum[2] += n.second->get_stress_spectrum()[2];
                    stress_sum[3] += n.second->get_stress_spectrum()[3];
                    infNeighbours++;
                }
            }
            if (infNeighbours == 0){
                continue;
            }
            double norm = (infNeighbours);
            sigma[0] = 1 - (stress_sum[0]/infNeighbours) * MATERIAL_ELASTICITY_PERCENTAGE;
            sigma[1] = 1 - (stress_sum[1]/infNeighbours) * MATERIAL_ELASTICITY_PERCENTAGE;
            sigma[2] = 1 - (stress_sum[2]/infNeighbours) * MATERIAL_ELASTICITY_PERCENTAGE;
            sigma[3] = 1 - (stress_sum[3]/infNeighbours) * MATERIAL_ELASTICITY_PERCENTAGE;

            std::vector<double> stress_spectrum = this->cells[x][y]->get_stress_spectrum();
            stress_spectrum[0] += sigma[0];
            stress_spectrum[1] += sigma[1];
            stress_spectrum[2] += sigma[2];
            stress_spectrum[3] += sigma[3];
            this->next_cells[x][y]->set_stress_spectrum(stress_spectrum);
            //cout << "=== JOE ===" << endl;
            //cout << stress_sum[0] << " " << stress_sum[1] << " " << stress_sum[2] << " " << stress_sum[3] << endl;
            ////cout << norm << endl;
            //cout << sigma[0] << " " << sigma[1] << " " << sigma[2] << " " << sigma[3] << endl;
            //cout << "=== COCK ===" << endl;
        }
    }
}

unordered_map<string, Cell*> Map::get_neigh(int x, int y){

    unordered_map<string, Cell*> result;

    result["TOP"] = this->cells[x][y-1];
    result["TOP_RIGHT"] = this->cells[x+1][y-1];
    result["TOP_LEFT"] = this->cells[x-1][y-1];
    result["RIGHT"] = this->cells[x+1][y];
    result["BOTTOM_RIGHT"] = this->cells[x+1][y+1];
    result["BOTTOM"] = this->cells[x][y+1];
    result["BOTTOM_LEFT"] = this->cells[x-1][y+1];
    result["LEFT"] = this->cells[x-1][y];
    return result;
}

Map::Map(unsigned int width, unsigned int height){
    this->width = width;
    this->height = height;

    this->cells = allocate_cells();

    this->next_cells = allocate_cells();

    this->stress_relaxation();
    this->copy_cells(this->next_cells, this->cells);
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
    
    default_random_engine generator;
    normal_distribution<double> distribution(MATERIAL_TOLERANCE / 1.5, (MATERIAL_TOLERANCE / 5) );

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
    for (unsigned int i = 0; i < this->width; i++)
    {
        for (unsigned int j = 0; j < this->height; j++)
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