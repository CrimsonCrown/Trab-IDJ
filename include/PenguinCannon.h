#ifndef PENGUINCANNON_INCLUDE
#define PENGUINCANNON_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <queue>

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "Timer.h"

class PenguinCannon : public Component{
public:
	PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Shoot();
private:
	bool cooldown;
	Timer cdtimer;
	std::weak_ptr<GameObject> pbody;
	float angle;
};

#endif