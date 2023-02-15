#ifndef SIGHTVIEW_INCLUDE
#define SIGHTVIEW_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#define PI 3.1415926

#include <iostream>
#include <string>
#include <queue>

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "Bullet.h"

class SightView : public Component{
public:
	SightView(GameObject& associated, std::weak_ptr<GameObject> eyeCenter, float arc, float range);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
	void SetNewPos();
	std::weak_ptr<GameObject> eyeCenter;
	float arc;
};

#endif