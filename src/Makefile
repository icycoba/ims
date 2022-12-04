ifeq ($(OS),Windows_NT)
# Windows
# Path: src\Makefile
	DEL := del *.o *.exe
	LIBS := -ID:\SDL2\i686-w64-mingw32\include -LD:\SDL2\i686-w64-mingw32\lib -lSDL2
else 
# Linux
# Path: src/Makefile
	DEL := rm -f *.o cracksim
	LIBS=-lSDL2
endif

CXX=g++
CXXFLAGS=-g -Wall -Wextra -std=c++17

all: cracksim

cracksim: cell.o crackmodule.o window.o map.o main.o 
	$(CXX) $(CXXFLAGS) main.o cell.o crackmodule.o window.o map.o -o cracksim  $(LIBS)

main.o: main.cc main.hh map.hh cell.hh window.hh
	$(CXX) $(CXXFLAGS) -c main.cc $(LIBS)

window.o: window.cc window.hh map.hh cell.hh
	$(CXX) $(CXXFLAGS) -c window.cc $(LIBS)

map.o: map.cc map.hh
	$(CXX) $(CXXFLAGS) -c map.cc $(LIBS)

crackmodule.o: crackmodule.cc crackmodule.hh
	$(CXX) $(CXXFLAGS) -c crackmodule.cc $(LIBS)

cell.o: cell.cc cell.hh
	$(CXX) $(CXXFLAGS) -c cell.cc

clean:
	$(DEL)
