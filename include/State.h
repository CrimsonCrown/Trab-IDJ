#ifndef STATE_INCLUDE
#define STATE_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Sprite.h"
#include "Music.h"

class State{
public:
	State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
private:
	Sprite bg;
	Music music;
	bool quitRequested;
};

#endif