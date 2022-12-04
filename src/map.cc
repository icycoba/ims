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

void Map::apply_rule(SDL_Surface *new_surface)
{

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
                if ( intensity > MATERIAL_TOLERANCE){
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

Cell *** Map::allocate_cells()
{
    
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