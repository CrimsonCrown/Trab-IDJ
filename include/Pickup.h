#ifndef PICKUP_INCLUDE
#define PICKUP_INCLUDE

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
#include "TileCoords.h"

class Pickup : public Component{
public:
	enum Type{MUFFLE, HEALTH};
	Pickup(GameObject& associated, TileCoords position, Type pt, float tileSize);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void NotifyCollision(GameObject& other);
	Type GetType();
private:
	std::string GetSprite();
	Type pt;
};

#endif