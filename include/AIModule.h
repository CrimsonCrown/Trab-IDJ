#ifndef AIMODULE_INCLUDE
#define AIMODULE_INCLUDE

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

class AIModule : public Component {
public:
	AIModule(GameObject& associated, float tileSize, float facingDirection = 0);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void AddVision(float range, float angle);
	void AddChaser(float tileSpeed);
	void See(Vec2 location);
	void Hear(Vec2 location);
	void Smell(Vec2 location);
	void Route(Vec2 location);
	float FacingDirection();
	void ChangeDirection(float newdir);
private:
	float facingDirection;
	float tileSize;
	bool vision;
	bool chaser;
};

#endif