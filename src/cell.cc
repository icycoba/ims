/**
 * @file cell.cc
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Zdrojový soubor buňky pro simulaci praskliny
 * @version 0.1
 * @date 2022-11-30
 */

#include "cell.hh"

Cell::Cell(){
    this->x = 0;
    this->y = 0;
    this->state = CellState::Intact;
    this->stressSpectrum = {0, 0, 0, 0};
}

Cell::~Cell(){
    
}

pair<int, int> Cell::get_coordinates(){
    return make_pair(this->x, this->y);
}

CellState Cell::get_state(){
    return this->state;
}

void Cell::set_x(int x){
    this->x = x;
}

void Cell::set_y(int y){
    this->y = y;
}

void Cell::set_coordinates(int x, int y){
    this->x = x;
    this->y = y;
}

void Cell::set_state(CellState state){
    this->state = state;
}