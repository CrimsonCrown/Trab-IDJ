#ifndef TILEMOVER_INCLUDE
#define TILEMOVER_INCLUDE

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

class TileMover : public Component {
public:
	TileMover(GameObject& associated, float tileSize);
	void Update(float dt);
	void Dash();
	void Render();
	bool Is(std::string type);
	void Reset();
private:
	enum MovementState { MOVING, RESTING, DASHING };
	MovementState state;
	Vec2 destination;
	float tileSize;
	float tileSpeed;
};

#endif