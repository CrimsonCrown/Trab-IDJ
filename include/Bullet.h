#ifndef BULLET_INCLUDE
#define BULLET_INCLUDE

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

class Bullet : public Component{
public:
	Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	int GetDamage();
private:
	Vec2 speed;
	float disanceLeft;
	int damage;
};

#endif