#ifndef DECOY_INCLUDE
#define DECOY_INCLUDE

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
#include "Timer.h"

class Decoy : public Component {
public:
	Decoy(GameObject& associated, float tileSize);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
	float tileSize;
    float noiseRadius;
    Timer timer;
};

#endif