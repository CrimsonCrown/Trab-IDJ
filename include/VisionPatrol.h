#ifndef VISIONPATROL_INCLUDE
#define VISIONPATROL_INCLUDE

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
class AngleCommand {
public:
	float angle;
	float waitTime;
};

class VisionPatrol : public Component {
public:
	VisionPatrol(GameObject& associated, float tileSize, std::vector<AngleCommand> commands);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
	std::vector<AngleCommand> commands;
	int maxCommands;
	int currentCommand;
	Timer timeElapsed;
	bool there;
	float tileSize;
};

#endif