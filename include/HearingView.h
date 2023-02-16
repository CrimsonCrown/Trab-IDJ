#ifndef HEARINGVIEW_INCLUDE
#define HEARINGVIEW_INCLUDE

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

class HearingView : public Component{
public:
	HearingView(GameObject& associated, std::weak_ptr<GameObject> earCenter);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Play();
private:
	bool playing;
	Timer durTimer;
	void SetNewPos();
	std::weak_ptr<GameObject> earCenter;
};

#endif