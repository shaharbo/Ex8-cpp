CXX=clang++-5.0
CXXFLAGS=-std=c++17

all: Board.o Node.o

Board.o: Board.cpp Board.h
	$(CXX) $(CXXFLAGS) -c Board.cpp -o Board.o

Node.o: Node.cpp Node.h
	$(CXX) $(CXXFLAGS) -c Node.cpp -o Node.o

main.o: main.cpp Board.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm *.o a.out

buildAndRun: all main.o
	$(CXX) $(CXXFLAGS) Board.o Node.o main.o
	./a.out < board3.txt
