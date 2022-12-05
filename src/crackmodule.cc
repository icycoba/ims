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

CrackModule::CrackModule(uint x, uint y, double kineticPotential)
{
    this->x = x;
    this->y = y;
    this->kineticPotential = kineticPotential * (1-MATERIAL_ELASTICITY_PERCENTAGE);
    this->directionEnum = Direction::NONE;
}

CrackModule::~CrackModule(){
    
}

pair<int, int> CrackModule::get_coordinates()
{
    return make_pair(this->x, this->y);
}

double CrackModule::get_kinetic_potential(){
    return this->kineticPotential;
}

Direction CrackModule::get_direction_enum(){
    return this->directionEnum;
}

void CrackModule::set_kinetic_potential(double kineticPotential){
    this->kineticPotential += kineticPotential;
}

void CrackModule::move_in_direction(){
    pair<int, int> direction = this->direction;
    this->x += direction.first;
    this->y += direction.second;
}

void CrackModule::set_direction(Direction direction_enum)
{
    this->direction = map_direction(direction_enum);
}

void CrackModule::set_direction_enum(Direction direction){
    this->directionEnum = direction;
    this->set_direction(direction);
}

Direction map_stress_field(uint index, bool head)
{
    switch (index)
    {
    case 0:
        return head ? Direction::RIGHT : Direction::LEFT;
    case 1:
        return head ? Direction::TOP_RIGHT : Direction::BOTTOM_LEFT;
    case 2:
        return head ? Direction::TOP : Direction::BOTTOM;
    case 3:
        return head ? Direction::TOP_LEFT : Direction::BOTTOM_RIGHT;
    default:
        return Direction::NONE;
    }
}

pair<int, int> map_direction(Direction direction_enum)
{
    pair<int, int> result;
    switch (direction_enum)
    {
    case Direction::TOP:
        result = make_pair(0, -1);
        break;
    case Direction::TOP_LEFT:
        result = make_pair(-1, -1);
        break;
    case Direction::TOP_RIGHT:
        result = make_pair(+1, -1);
        break;
    case Direction::LEFT:
        result = make_pair(-1, 0);
        break;
    case Direction::RIGHT:
        result = make_pair(+1, 0);
        break;
    case Direction::BOTTOM:
        result = make_pair(0, +1);
        break;
    case Direction::BOTTOM_LEFT:
        result = make_pair(-1, +1);
        break;
    case Direction::BOTTOM_RIGHT:
        result = make_pair(+1, +1);
        break;

    default:
        result = make_pair(0, 0);
        break;
    }
    return result;
}
