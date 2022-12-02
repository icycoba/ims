CXX=g++
CXXFLAGS=-g -Wall -Wextra -std=c++17
LIBS=-lSDL2 

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
	rm -f *.o cracksim