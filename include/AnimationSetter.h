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
	AnimationSetter(GameObject& associated, float tileSpeed, std::string name);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void SetIdle();
	void SetIdleLeft();
	void SetIdleRight();
	void SetRunLeft();
	void SetRunRight();
	void UpdateSpeed(float newspeed);
private:
	void LoadIndexes(std::string name);
	int indexes[2][2][2];
	int frames;
	float tileSpeed;
	int state1;
	int state2;
};

#endif