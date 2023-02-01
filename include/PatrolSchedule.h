#ifndef PATROLSCHEDULE_INCLUDE
#define PATROLSCHEDULE_INCLUDE

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

class PatrolCommand {
public:
	TileCoords location;
	float waitTime;
};

class PatrolSchedule : public Component {
public:
	PatrolSchedule(GameObject& associated, float tileSize, std::vector<PatrolCommand> commands);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
	std::vector<PatrolCommand> commands;
	int maxCommands;
	int currentCommand;
	Timer timeElapsed;
	bool there;
	float tileSize;
};

#endif