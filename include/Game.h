#ifndef GAME_INCLUDE
#define GAME_INCLUDE


#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stack>

#include "State.h"
#include "InputManager.h"

class Game{
public:
	~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetCurrentState();
	static Game& GetInstance();
	float GetDeltaTime();
	void Push(State* state);
private:
	Game(const char* title, int width, int height);
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int frameStart;
	float dt;
	void CalculateDeltaTime();
	State* storedState;
	std::stack<std::unique_ptr<State>> stateStack;
};

#endif