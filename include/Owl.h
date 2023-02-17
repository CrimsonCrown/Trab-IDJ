#ifndef OWL_INCLUDE
#define OWL_INCLUDE

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
#include "PatrolSchedule.h"
#include "VisionChaser.h"
#include "VisionPatrol.h"

class Owl : public Component {
public:
	Owl(GameObject& associated, float tileSize, std::vector<AngleCommand> commands);
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
};

#endif