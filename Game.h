#ifndef GAME_INCLUDE
#define GAME_INCLUDE


#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "State.h"

class Game{
public:
	~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance();
private:
	Game(const char* title, int width, int height);
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
};

#endif