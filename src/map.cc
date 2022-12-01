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

Map::Map(){
    this->width = 100;
    this->height = 100;
}

Map::Map(unsigned int width, unsigned int height){
    this->width = width;
    this->height = height;
}

Map::~Map(){

}

int Map::get_width(){
    return this->width;
}

int Map::get_height(){
    return this->height;
}

std::vector<std::vector<Cell>> Map::get_cells(){
    return this->cells;
}

void Map::set_width(unsigned int width){
    this->width = width;
}

void Map::set_height(unsigned int height){
    this->height = height;
}
