#ifndef HEALTHBAR_INCLUDE
#define HEALTHBAR_INCLUDE

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

class HealthBar : public Component {
public:
	HealthBar(GameObject& associated);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
};

#endif