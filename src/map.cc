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

#define GAUSS abs(distribution(generator))

bool is_set_state(CellState state)
{
    return state == CellState::Cracked;
}

bool stress_gt_tolerance(vector<double> stress, uint index){
    return stress[index] > MATERIAL_TOLERANCE - 4;

}
uint vector_length(pair<int, int> bgn, pair<int,int> end){
    return abs(sqrt((end.first - bgn.first) * (end.first - bgn.first) + (end.second - bgn.second) * (end.second - bgn.second)));
}

void CMCrack(CrackModule *cm, Cell*** cells, SDL_Surface *new_surface){

    cerr << "ceakc step" << endl;

    if (cm->get_direction_enum() == Direction::NONE){
        cerr << "no move"<< endl;
        return;
    }
    //is cell cracked
    //cout << x << " " << y << endl;

    cm->move_in_direction();
    pair<int, int> here = cm->get_coordinates();

    if (here.first <= 0 || here.second <= 0)
    {
        cm->set_direction_enum(Direction::NONE);
        cout << "not ostnsad vazne" << endl;
        return;
    }
    if (here.first >= 1000 || here.second >= 720)
    {
        cm->set_direction_enum(Direction::NONE);
        cout << "joe mama" << endl;
        return;
    }
    if (cells[here.first][here.second]->get_state() == CellState::Cracked)
    {
        //cout << "r u crazy???" << endl;
        cm->set_direction_enum(Direction::NONE);
        cout << "ball crusher" << endl;
        return;
    }
    
    cells[here.first][here.second]->set_pixel(new_surface, WHITE);

    uint maxIntensityIndex = cells[here.first][here.second]->maximum_stress();

    double kineticPotential = cells[here.first][here.second]->get_stress_spectrum()[maxIntensityIndex];
    kineticPotential = (kineticPotential - MATERIAL_TOLERANCE) * 0.05;
    cm->set_kinetic_potential(kineticPotential);
    
    if(cm->get_kinetic_potential() < 0.1){
        cout << "holdup" << endl;
        cm->set_direction_enum(Direction::NONE);
        return;
    }

    // stress release

    Direction head_direction = map_stress_field(maxIntensityIndex, true);
    Direction tail_direction = map_stress_field(maxIntensityIndex, false);

    pair<int, int> head_coord = map_direction(head_direction);
    pair<int, int> tail_coord = map_direction(tail_direction);
    pair<int, int> next_coord = map_direction(cm->get_direction_enum());

    uint lengthHead = vector_length(make_pair(here.first + next_coord.first, here.second + next_coord.second), make_pair(here.first + head_coord.first, here.second + head_coord.second));
    uint lengthTail = vector_length(make_pair(here.first + next_coord.first, here.second + next_coord.second), make_pair(here.first + tail_coord.first, here.second + tail_coord.second));

    if (lengthHead == lengthTail){
        // todo handle the T fork
        cm->set_direction_enum(Direction::NONE);
        cout << "forkec" << endl;
        return;
    }

    lengthHead < lengthTail ? cm->set_direction_enum(head_direction) : cm->set_direction_enum(tail_direction);

    //cout << "=============================================" << endl;
    //cout << "direction: " << direction.first << " " << direction.second << endl;
    //cout << "xhead: "   << xHead << " yhead: " << yHead << endl;
    //cout << "xtail: "   << xTail << " ytail: " << yTail << endl;
    //cout << "=============================================" << endl;
    
    
    //cout << "lengthHead: " << lengthHead << endl;
    //cout << "lengthTail: " << lengthTail << endl;
}

pair<CrackModule*, CrackModule*> *crack_birth(uint x, uint y, uint index)
{

    uint starting_kinetic_potential = 196 * (1 - MATERIAL_ELASTICITY_PERCENTAGE);
    CrackModule *cmHead = new CrackModule(x, y, starting_kinetic_potential);
    CrackModule *cmTail = new CrackModule(x, y, starting_kinetic_potential);

    cmHead->set_direction_enum(map_stress_field(index, true));
    cmTail->set_direction_enum(map_stress_field(index, false));

    return new pair<CrackModule *, CrackModule *>(cmHead, cmTail);
}

void Map::apply_rule(SDL_Surface *new_surface, vector<pair<Cell *, double>> *unstable_list, vector<pair<CrackModule*, CrackModule*>*> *crack_list)
{
    if(!unstable_list->empty()){

        Cell *cell = unstable_list->back().first;
        unstable_list->pop_back();
        
        pair<uint, uint> coord = cell->get_coordinates();

        // set pixel white
        cell->set_pixel(new_surface, WHITE);

        uint maxIntensityIndex = cell->maximum_stress();
        pair<CrackModule*, CrackModule*> *new_crack_pair = crack_birth(coord.first, coord.second, maxIntensityIndex);
        crack_list->push_back(new_crack_pair);
    }
    else{
        //cerr << "no unstable cells left" << endl;
    }
    if (!crack_list->empty()){
        
        Cell ***cells = this->get_cells();
        for (vector<pair<CrackModule *, CrackModule *>*>::iterator crack_pair = crack_list->begin(); crack_pair != crack_list->end();)
        {
            cout << "dřez nuts" << endl;
            CMCrack((*crack_pair)->first, cells, new_surface);
            CMCrack((*crack_pair)->second, cells, new_surface);
            if ((*crack_pair)->first->get_direction_enum() == Direction::NONE && (*crack_pair)->second->get_direction_enum() == Direction::NONE){
                delete (*crack_pair)->first;
                delete (*crack_pair)->second;
                delete *crack_pair;
                crack_pair = crack_list->erase(crack_pair);
            }
                
            else
                ++crack_pair;
        }
    }
    else
    {
        //cerr << "no CM left" << endl;
    }
}

void Map::set_unstable(vector<pair<Cell *, double>> *unstable_list)
{
    for (uint x = 0; x < this->width; x++)
    {
        for (uint y = 0; y < this->height; y++)
        {
            if (this->cells[x][y]->get_state() != CellState::Cracked){
                uint maxIndex = this->cells[x][y]->maximum_stress();
                double intensity = this->cells[x][y]->get_stress_spectrum()[maxIndex];
                if ( (uint)intensity > MATERIAL_TOLERANCE + 2){
                    cout << intensity << endl;
                    unstable_list->push_back(pair<Cell*,double>(this->cells[x][y], intensity));
                }
            }
            
        }
    }
}

void Map::stress_relaxation(){

    for(uint x = 1; x < this->width-1; x++){
        for(uint y = 1; y < this->height-1; y++){
            
            vector<double> sigma = {0, 0, 0, 0};
            double my_stress = this->cells[x][y]->get_stress_avg();
            vector<double> stress_sum = {0,0,0,0};

            unordered_map<string, Cell*> neighs = this->get_neigh(x,y);
            uint infNeighbours = 0;

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
            double norm = MATERIAL_ELASTICITY_PERCENTAGE /(infNeighbours);
            sigma[0] = 1 - stress_sum[0] * norm;
            sigma[1] = 1 - stress_sum[1] * norm;
            sigma[2] = 1 - stress_sum[2] * norm;
            sigma[3] = 1 - stress_sum[3] * norm;

            std::vector<double> stress_spectrum = this->cells[x][y]->get_stress_spectrum();
            stress_spectrum[0] += sigma[0];
            stress_spectrum[1] += sigma[1];
            stress_spectrum[2] += sigma[2];
            stress_spectrum[3] += sigma[3];
            this->next_cells[x][y]->set_stress_spectrum(stress_spectrum);
        }
    }
}

unordered_map<string, Cell*> Map::get_neigh(uint x, uint y){

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

Map::Map(uint width, uint height){
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

uint Map::get_width(){
    return this->width;
}

uint Map::get_height(){
    return this->height;
}

Cell *** Map::get_cells(){
    return this->cells;
}

Cell *** Map::allocate_cells()
{
    
    default_random_engine generator;
    normal_distribution<double> distribution(MATERIAL_TOLERANCE / 1.5, (MATERIAL_TOLERANCE / 5) );

    Cell *** result = new Cell **[this->width];

    for (uint x = 0; x < this->width; x++)
    {
        Cell **row = new Cell*[this->height];
        result[x] = row;
        for (uint y = 0; y < this->height; y++)
        {
            result[x][y] = new Cell(x, y, {GAUSS, GAUSS, GAUSS, GAUSS});
        }
        
    }
    return result;
}

void Map::free_cells(Cell ***cells)
{
    for (uint x = 0; x < this->width; x++)
    {
        for (uint y = 0; y < this->height; y++)
        {
            delete cells[x][y];
        }
        delete cells[x];
    }
    delete cells;
}

void Map::copy_cells(Cell *** src, Cell *** dst)
{
    for (uint x = 0; x < this->width; x++)
    {
        for (uint y = 0; y < this->height; y++)
        {
            *dst[x][y] = *src[x][y];
        }
    }
}