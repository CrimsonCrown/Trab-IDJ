#ifndef HEARING_INCLUDE
#define HEARING_INCLUDE

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

class Hearing : public Component {
public:
	Hearing(GameObject& associated, float sensibility);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
    void NotifyCollision(GameObject& other);
private:
	float sensibility;
};

#endif