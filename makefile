all: main.o 
	g++ -o out main.cpp -std=c++17 -g
main.o: 
	g++ -c main.cpp -std=c++17
