#ifndef ALIEN_INCLUDE
#define ALIEN_INCLUDE

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

class Alien : public Component{
public:
	Alien(GameObject& associated, int nMinions, float alienDelay);
	~Alien();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void NotifyCollision(GameObject& other);
	static int alienCount;
private:
	enum AlienState {MOVING,RESTING};
	AlienState state;
	Timer restTimer;
	Vec2 destination;
	Vec2 speed;
	float alienDelay;
	int hp;
	std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif