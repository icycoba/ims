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

void CMCrack(CrackModule cm, Cell*** cells, int x, int y, SDL_Surface *new_surface){
    //is cell cracked
    //cout << x << " " << y << endl;
    if(x < 0 || y < 0){
        return;
    }
    if(x >= 1000 || y >= 720){
        return;
    }
    if (cells[x][y]->get_state() == CellState::Cracked)
    {
        cout << "r u crazy???" << endl;
        return;
    }
    
    cells[x][y]->set_pixel(new_surface, WHITE);
    cells[x][y]->set_state(CellState::Cracked);
    int maxIntensityIndex = cells[x][y]->maximum_stress();

    int xHead = x;
    int yHead = y;
    int xTail = x;
    int yTail = y;

    Direction directionEnumHead = Direction::NONE;
    Direction directionEnumTail = Direction::NONE;

    switch (maxIntensityIndex)
    {
    case 0:
        xHead = x + 1;
        xTail = x - 1;
        directionEnumHead = Direction::RIGHT;
        directionEnumTail = Direction::LEFT;
        break;
    case 1:
        xHead = x + 1;
        xTail = x - 1;
        yHead = y - 1;
        yTail = y + 1;
        directionEnumHead = Direction::TOP_RIGHT;
        directionEnumTail = Direction::BOTTOM_LEFT;
        break;
    case 2:
        yHead = y + 1;
        yTail = y - 1;
        directionEnumHead = Direction::BOTTOM;
        directionEnumTail = Direction::TOP;
        break;
    case 3:
        xHead = x + 1;
        xTail = x - 1;
        yHead = y + 1;
        yTail = y - 1;
        directionEnumHead = Direction::BOTTOM_RIGHT;
        directionEnumTail = Direction::TOP_LEFT;
        break;
    default:
        cout << "what???" << endl;
        break;
    }

    double kineticPotential = cells[x][y]->get_stress_spectrum()[maxIntensityIndex];
    kineticPotential = (kineticPotential - MATERIAL_TOLERANCE) * 0.05;
    cm.set_kinetic_potential(kineticPotential);
    double temp = cm.get_kinetic_potential();
    if(temp < 0.1){
        cout << "holdup" << endl;
        return;
    }
    pair <int, int> direction;

    if(cm.get_direction_enum() == Direction::TOP){
        direction = make_pair(x,y-1);
    } else if(cm.get_direction_enum() == Direction::TOP_RIGHT){
        direction = make_pair(x+1,y-1);
    } else if(cm.get_direction_enum() == Direction::RIGHT){
        direction = make_pair(x+1,y);
    } else if(cm.get_direction_enum() == Direction::BOTTOM_RIGHT){
        direction = make_pair(x+1,y+1);
    } else if(cm.get_direction_enum() == Direction::BOTTOM){
        direction = make_pair(x,y+1);
    } else if(cm.get_direction_enum() == Direction::BOTTOM_LEFT){
        direction = make_pair(x-1,y+1);
    } else if(cm.get_direction_enum() == Direction::LEFT){
        direction = make_pair(x-1,y);
    } else if(cm.get_direction_enum() == Direction::TOP_LEFT){
        direction = make_pair(x-1,y-1);
    } else if(cm.get_direction_enum() == Direction::NONE){
        cout << "not possible" << endl;
        return;
    }

    //cout << "=============================================" << endl;
    //cout << "direction: " << direction.first << " " << direction.second << endl;
    //cout << "xhead: "   << xHead << " yhead: " << yHead << endl;
    //cout << "xtail: "   << xTail << " ytail: " << yTail << endl;
    //cout << "=============================================" << endl;
    int lengthHead = abs(sqrt((direction.first-xHead)*(direction.first-xHead) + (direction.second-yHead)*(direction.second-yHead)));
    int lengthTail = abs(sqrt((direction.first-xTail)*(direction.first-xTail) + (direction.second-yTail)*(direction.second-yTail)));
    //cout << "lengthHead: " << lengthHead << endl;
    //cout << "lengthTail: " << lengthTail << endl;
    /*if(lengthHead == lengthTail){
        CrackModule cmHead = CrackModule(xHead, yHead, 14*14 //kineticPotential, directionEnumHead);
        CMCrack(cmHead, cells, xHead, yHead, new_surface);
        CrackModule cmTail = CrackModule(xTail, yTail, 14*14 //kineticPotential, directionEnumTail);
        CMCrack(cmTail, cells, xTail, yTail, new_surface);
    } else*/ if(lengthHead < lengthTail){
        //cout << "here" << endl;
        //cout << xHead << " " << yHead << endl;
        cm.set_direction(make_pair(xHead, yHead));
        //cm.set_direction_enum(directionEnumHead);
        CMCrack(cm, cells, xHead, yHead, new_surface);
    } else{
        cm.set_direction(make_pair(xTail, yTail));
        //cm.set_direction_enum(directionEnumTail);
        CMCrack(cm, cells, xTail, yTail, new_surface);
    }
}


void Map::apply_rule(SDL_Surface *new_surface, vector<pair<Cell*, double>> unstable)
{
    for (int i = 0; i < 150 ; i++){
        if (i > unstable.size()){
            break;
        }
    Cell *cell = unstable[i].first;
    pair<int, int> coord = cell->get_coordinates();
    int x = coord.first;
    int y = coord.second;
    Cell ***cells = this->get_cells();

    // set pixel white
    cell->set_pixel(new_surface, WHITE);
    cell->set_state(CellState::Cracked);

    int maxIntensityIndex = cell->maximum_stress();

    int xHead = x;
    int yHead = y;
    int xTail = x;
    int yTail = y;
    Direction directionEnumHead = Direction::NONE;
    Direction directionEnumTail = Direction::NONE;
    
    switch (maxIntensityIndex)
    {
    case 0:
        xHead = x + 1;
        xTail = x - 1;
        directionEnumHead = Direction::RIGHT;
        directionEnumTail = Direction::LEFT;
        break;
    case 1:
        xHead = x + 1;
        xTail = x - 1;
        yHead = y - 1;
        yTail = y + 1;
        directionEnumHead = Direction::TOP_RIGHT;
        directionEnumTail = Direction::BOTTOM_LEFT;
        break;
    case 2:
        yHead = y + 1;
        yTail = y - 1;
        directionEnumHead = Direction::BOTTOM;
        directionEnumTail = Direction::TOP;
        break;
    case 3:
        xHead = x + 1;
        xTail = x - 1;
        yHead = y + 1;
        yTail = y - 1;
        directionEnumHead = Direction::BOTTOM_RIGHT;
        directionEnumTail = Direction::TOP_LEFT;
        break;
    default:
        break;
    }
    cout << xHead << " " << yHead << " " << xTail << " " << yTail << endl;

    pair<int,int> directionHead = make_pair(xHead, yHead);
    pair<int,int> directionTail = make_pair(xTail, yTail);

    CrackModule cmHead = CrackModule(xHead, yHead, 14*14 /*kineticPotential*/, directionEnumHead);
    CMCrack(cmHead, cells, xHead, yHead, new_surface);
    CrackModule cmTail = CrackModule(xTail, yTail, 14*14 /*kineticPotential*/, directionEnumTail);
    CMCrack(cmTail, cells, xTail, yTail, new_surface);
    }


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

Cell *** Map::allocate_cells()
{
    
    default_random_engine generator;
    normal_distribution<double> distribution(MATERIAL_TOLERANCE / 1.5, (MATERIAL_TOLERANCE / 5) );

    Cell *** result = new Cell **[this->width];

    for (unsigned int x = 0; x < this->width; x++)
    {
        Cell **row = new Cell*[this->height];
        result[x] = row;
        for (unsigned int y = 0; y < this->height; y++)
        {
            result[x][y] = new Cell(x, y, {GAUSS, GAUSS, GAUSS, GAUSS});
        }
        
    }
    return result;
}

void Map::free_cells(Cell ***cells)
{
    for (unsigned int x = 0; x < this->width; x++)
    {
        for (unsigned int y = 0; y < this->height; y++)
        {
            delete cells[x][y];
        }
        delete cells[x];
    }
    delete cells;
}

void Map::copy_cells(Cell *** src, Cell *** dst)
{
    for (unsigned int x = 0; x < this->width; x++)
    {
        for (unsigned int y = 0; y < this->height; y++)
        {
            *dst[x][y] = *src[x][y];
        }
    }
}