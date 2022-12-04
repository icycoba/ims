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
#include <ctime>
#include <stdlib.h>

Cell::Cell(){
    this->x = 0;
    this->y = 0;
    this->state = CellState::Intact;
    this->stressSpectrum = {0, 0, 0, 0};
}
Cell::Cell(unsigned int i, unsigned int j, vector<double> stressSpectrum)
{
    this->x = i;
    this->y = j;
    this->state = CellState::Default;
    this->stressSpectrum = stressSpectrum;
}

Cell::~Cell(){
    
}

pair<int, int> Cell::get_coordinates(){
    return make_pair(this->x, this->y);
}

CellState Cell::get_state(){
    return this->state;
}

vector<double> Cell::get_stress_spectrum(){
    return this->stressSpectrum;
}

double Cell::get_stress_avg(){
    double sum = 0;
    for (int i = 0; i < 4; i++)
    {
        sum += this->stressSpectrum[i];
    }
    return sum / 4;
}

void Cell::set_coordinates(int x, int y){
    this->x = x;
    this->y = y;
}

void Cell::set_state(CellState state){
    this->state = state;
}

void Cell::set_stress_spectrum(vector<double> stressSpectrum){
    this->stressSpectrum = stressSpectrum;
}

int Cell::maximum_stress(){
    int maxIndex = 0;
    double max = 0;
    for (int i = 0; i < 4; i++){
        if (this->stressSpectrum[i] > max){
            maxIndex = i;
            max = this->stressSpectrum[i];
        }
    }
    return maxIndex;
}