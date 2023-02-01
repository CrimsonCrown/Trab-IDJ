#ifndef RAT_INCLUDE
#define RAT_INCLUDE

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

class Rat : public Component {
public:
	Rat(GameObject& associated, float tileSize, std::vector<PatrolCommand> commands);
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void NotifyCollision(GameObject& other);
private:
	int hp;
};

#endif