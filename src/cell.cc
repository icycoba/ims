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
    this->state = 0;
}

Cell::~Cell(){
    
}

int Cell::get_x(){
    return this->x;
}

int Cell::get_y(){
    return this->y;
}

int Cell::get_state(){
    return this->state;
}

void Cell::set_x(int x){
    this->x = x;
}

void Cell::set_y(int y){
    this->y = y;
}

void Cell::set_state(int state){
    this->state = state;
}