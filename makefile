all: main
 
main: Game State Sprite
	g++ -std=c++11 -g -Wall main.cpp Game.o State.o Sprite.o -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Game:
	g++ -std=c++11 -c -g -Wall Game.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

State:
	g++ -std=c++11 -c -g -Wall State.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

Sprite:
	g++ -std=c++11 -c -g -Wall Sprite.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

clean:
	rm -rf *.o *~