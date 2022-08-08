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
	Alien(GameObject& associated, int nMinions);
	~Alien();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
	class Action{
	public:
		enum ActionType {MOVE,SHOOT};
		Action(ActionType type, float x, float y){
			this->type=type;
			pos.x=x;
			pos.y=y;
		};
		ActionType type;
		Vec2 pos;
	private:
	};
	Vec2 speed;
	int hp;
	std::queue<Action> taskQueue;
	std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif