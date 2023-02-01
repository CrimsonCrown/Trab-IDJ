#ifndef ANIMATIONSETTER_INCLUDE
#define ANIMATIONSETTER_INCLUDE

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

class AnimationSetter : public Component {
public:
	AnimationSetter(GameObject& associated, float tileSpeed);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void SetIdle();
	void SetRunLeft();
	void UpdateSpeed(float newspeed);
private:
	int frames;
	float tileSpeed;
	int state;
};

#endif