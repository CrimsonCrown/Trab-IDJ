all: main
 
main: Game
	g++ -std=c++11 -g -Wall main.cpp Game.o

Game:
	g++ -std=c++11 -g -Wall Game.cpp

clean:
	rm -rf *.o *~