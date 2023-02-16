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
#include "TileCoords.h"

class TileChaser : public Component {
public:
	TileChaser(GameObject& associated, float tileSize, float tileSpeed);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void See(TileCoords location);
	void Hear(TileCoords location);
	void Smell(TileCoords location);
	void Route(TileCoords location);
private:
	enum MovementState { MOVING, RESTING };
	enum PerceptionState { SIGHT, HEARING, SMELL, LOOKING, PATROL, LOST };
	MovementState state;
	PerceptionState destinationType;
	TileCoords destination;
	TileCoords nextPos;
	std::deque<TileCoords> path;
	bool needspath;
	float tileSize;
	float tileSpeed;
	int lookedDir;
	Timer lookTimer;
};

#endif