#ifndef MUSHROOM_INCLUDE
#define MUSHROOM_INCLUDE

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

class Mushroom : public Component {
public:
	Mushroom(GameObject& associated);
	~Mushroom();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	static Mushroom* player;
	void NotifyCollision(GameObject& other);
	Vec2 Position();
private:
	Vec2 speed;
	float linearSpeed;
	int dir;//0 stop, 1 up, 2 right, 3 down, 4 left
	int hp;
};

#endif