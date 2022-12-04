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

CrackModule::CrackModule(int x, int y, double kineticPotential){
    this->x = x;
    this->y = y;
    this->kineticPotential = kineticPotential * 0.25;
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

void CrackModule::set_kinetic_potential(double kineticPotential){
    this->kineticPotential += kineticPotential;
}