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
#include <iostream>
#include <GL/glut.h>

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
void show_map(){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.0, 0.5);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glFlush();
}

void Map::print_map(int *argc, char **argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(this->get_width(), this->get_height());
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CrackSim ;)");
    glutDisplayFunc(show_map);
    glutMainLoop();
}
