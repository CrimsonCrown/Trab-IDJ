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
#include "Skill.h"
#include "TileCoords.h"

class Mushroom : public Component {
public:
	Mushroom(GameObject& associated, float tileSize, TileCoords initialPosition);
	~Mushroom();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	static Mushroom* player;
	void NotifyCollision(GameObject& other);
	Vec2 Position();
	void Place(TileCoords position);
	int GetHp();
	static const int maxskills=3;
	int currentskills;
	void Muffle();
	void Amplify();
	void SpeedUp();
	void SlowDown();
	float NoiseRadius();
	float TileSpeed();
	Skill* GetSkill(int index);
private:
	std::vector<std::weak_ptr<GameObject>> skills;
	float tileSize;
	float noiseRadius;
	float tileSpeed;
	TileCoords initialPosition;
	int hp;
};

#endif