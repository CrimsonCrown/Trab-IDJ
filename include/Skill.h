#ifndef SKILL_INCLUDE
#define SKILL_INCLUDE

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

class Skill : public Component{
public:
	enum Type{MUFFLE, SPEEDBOOST};
	Skill(GameObject& associated, Type st, std::weak_ptr<GameObject> player);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Use();
	std::string GetSprite();
	float GetActiveCooldown();
private:
	float GetCooldown();
	float GetDuration();
	Type st;
	bool active;
	bool coolingdown;
	Timer cdtimer;
	Timer drtimer;
	std::weak_ptr<GameObject> player;
};

#endif