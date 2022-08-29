#ifndef PENGUINBODY_INCLUDE
#define PENGUINBODY_INCLUDE

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

class PenguinBody : public Component{
public:
	PenguinBody(GameObject& associated);
	~PenguinBody();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	static PenguinBody* player;
	void NotifyCollision(GameObject& other);
	Vec2 Position();
private:
	std::weak_ptr<GameObject> pcannon;
	Vec2 speed;
	float linearSpeed;
	float angle;
	int hp;
};

#endif