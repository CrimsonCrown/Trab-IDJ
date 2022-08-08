#ifndef MINION_INCLUDE
#define MINION_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#define PI 3.1415926

#include <iostream>
#include <string>
#include <queue>

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"

const float ANGSPEED = PI/2;

class Minion : public Component{
public:
	Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Shoot(Vec2 target);
private:
	void SetNewPos();
	std::weak_ptr<GameObject> alienCenter;
	float arc;
};

#endif