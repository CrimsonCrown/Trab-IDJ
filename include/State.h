#ifndef STATE_INCLUDE
#define STATE_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#define PI 3.1415926

#include <iostream>
#include <string>
#include <memory>

#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "Face.h"

class State{
public:
	State();
	~State();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
private:
	void Input();
	void AddObject(int mouseX, int mouseY);
	std::vector<std::unique_ptr<GameObject>> objectArray;
	Music music;
	bool quitRequested;
};

#endif