#ifndef TIMER_INCLUDE
#define TIMER_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <queue>

class Timer{
public:
	Timer();
	void Update(float dt);
	void Restart();
	float Get();
private:
	float time;
};

#endif