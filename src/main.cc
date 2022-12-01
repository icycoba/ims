/**
 * @file main.cc
 * @author Martin Hlinský (xhlins01)
 * @author Dziyana Khrystsiuk (xkhrys00)
 * 
 * @brief Zdrojový soubor, hlavní tělo programu
 * @version 0.1
 * @date 2022-11-30
 */

#include "main.hh"

#include <iostream>
#include <GL/glut.h>


void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.0, 0.5);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glFlush();
}


int main(int argc, char **argv){
    
    Map map = Map();

    std::vector <std::string> args(argv, argv+argc);
    if(args.size() > 1){
        for(std::string arg : args){
            if(arg == "--size" || arg == "-s"){
                if(args.size() > 3){
                    std::cout << "Size: " << args[2] << "x" << args[3] << std::endl;
                    map.set_height(stoul(args[3],nullptr,0));
                    map.set_width(stoul(args[2],nullptr,0));
                }
                else{
                    std::cerr << "Missing size argument" << std::endl;
                    return 1;
                }
            }
        }
    } else{
        //TODO - implement help print
        std::cout << "Usage:" << std::endl;
        std::cout << "\t--size, -s <width> <height>  Set size of the grid" << std::endl;
        std::cout << "\t\tDefault size is 100x100" << std::endl;
        std::cout << "\t\tWidth and height must be greater than 0" << std::endl;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(map.get_width(), map.get_height());
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CrackSim ;)");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}

