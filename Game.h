#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

class State{};

class Game{
public:
	~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetState();
	static Game& GetInstance();
	Game();
private:
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* state;
};