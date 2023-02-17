#ifndef VISIONCHASER_INCLUDE
#define VISIONCHASER_INCLUDE

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

class VisionChaser : public Component {
public:
	VisionChaser(GameObject& associated, float tileSize, float visionSpeed, float range);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void See(float angle);
	void SeeRoute(float angle);
private:
	enum PerceptionState { SIGHT, LOOKING, PATROL, LOST };
	PerceptionState destinationType;
	float destinationAngle;
	float nextPos;
	std::deque<float> path;
	bool needspath;
	float tileSize;
	float visionSpeed;
	int lookedDir;
	Timer lookTimer;
};

#endif