#ifndef VISION_INCLUDE
#define VISION_INCLUDE

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
#include "Minion.h"

class Vision : public Component {
public:
	Vision(GameObject& associated, float tileSize, float range, float angle);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Blocked();
private:
	Vec2 positionSeen;
	bool waitingCollision;
	float tileSize;
	float range;
	float angle;
};

#endif