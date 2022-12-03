ifeq ($(OS),Windows_NT)
# Windows
# Path: src\Makefile
	DEL := del *.o *.exe
	LIBS :=-ID:\SDL2\i686-w64-mingw32\include -LD:\SDL2\i686-w64-mingw32\lib
else 
# Linux
# Path: src/Makefile
	DEL := rm -f *.o cracksim
	LIBS=-lSDL2
endif

CXX=g++
CXXFLAGS=-g -Wall -Wextra -std=c++17

all: cracksim

cracksim: cell.o map.o main.o 
	$(CXX) $(CXXFLAGS) main.o cell.o map.o -o cracksim  $(LIBS)

main.o: main.cc main.hh cell.hh
	$(CXX) $(CXXFLAGS) -c main.cc

map.o: map.cc map.hh
	$(CXX) $(CXXFLAGS) -c map.cc $(LIBS)

cell.o: cell.cc cell.hh
	$(CXX) $(CXXFLAGS) -c cell.cc

clean:
	$(DEL)
