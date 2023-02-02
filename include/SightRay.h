#ifndef SIGHTRAY_INCLUDE
#define SIGHTRAY_INCLUDE

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
#include "Vision.h"

class SightRay : public Component{
public:
	SightRay(GameObject& associated, Vision& eye, Vec2 origin, Vec2 destiny, float girth, bool seeing);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void NotifyCollision(GameObject& other);
private:
	bool todie;
	bool seeing;
	Vision& eye;
};

#endif