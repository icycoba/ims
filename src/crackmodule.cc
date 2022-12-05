/**
 * @file crackmodule.cc
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Zdrojový soubor konce praskliny
 * @version 0.1
 * @date 2022-11-30
 */

#include "crackmodule.hh"

CrackModule::CrackModule(int x, int y, double kineticPotential, Direction direction){
    this->x = x;
    this->y = y;
    this->kineticPotential = kineticPotential * (1-MATERIAL_ELASTICITY_PERCENTAGE);
    this->directionEnum = direction;
}

CrackModule::~CrackModule(){
    
}

int CrackModule::get_x(){
    return this->x;
}

int CrackModule::get_y(){
    return this->y;
}

double CrackModule::get_kinetic_potential(){
    return this->kineticPotential;
}

pair<int, int> CrackModule::get_direction(){
    return this->direction;
}

Direction CrackModule::get_direction_enum(){
    return this->directionEnum;
}

void CrackModule::set_kinetic_potential(double kineticPotential){
    this->kineticPotential += kineticPotential;
}

void CrackModule::set_direction(pair<int, int> direction){
    this->direction = direction;
}

void CrackModule::set_direction_enum(Direction direction){
    this->directionEnum = direction;
}