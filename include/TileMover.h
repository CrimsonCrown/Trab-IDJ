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
	TileMover(GameObject& associated);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
	enum MovementState { MOVING, RESTING };
	MovementState state;
	Vec2 destination;
	Vec2 speed;
};

#endif