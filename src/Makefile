CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++17

all: cracksim

cracksim: main.o cell.o
	$(CXX) $(CXXFLAGS) main.o cell.o -o cracksim

main.o: main.cc main.hh cell.hh
	$(CXX) $(CXXFLAGS) -c main.cc

cell.o: cell.cc cell.hh
	$(CXX) $(CXXFLAGS) -c cell.cc

clean:
	rm -f *.o cracksim