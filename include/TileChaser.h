#ifndef TILECHASER_INCLUDE
#define TILECHASER_INCLUDE

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

class TileChaser : public Component {
public:
	TileChaser(GameObject& associated, float tileSize, float tileSpeed);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void See(Vec2 location);
	void Hear(Vec2 location);
	void Smell(Vec2 location);
	void Route(Vec2 location);
private:
	enum MovementState { MOVING, RESTING };
	enum PerceptionState { SIGHT, HEARING, SMELL, PATROL, LOST };
	MovementState state;
	PerceptionState destinationType;
	Vec2 destination;
	Vec2 nextPos;
	float tileSize;
	float tileSpeed;
};

#endif