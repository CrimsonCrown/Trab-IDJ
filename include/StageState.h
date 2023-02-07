#ifndef STAGESTATE_INCLUDE
#define STAGESTATE_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#define PI 3.1415926

#include <iostream>
#include <string>
#include <memory>

#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Mushroom.h"

class StageState : public State{
public:
	StageState(std::string mapfile = "Recursos/map/map1.txt", bool oldplayer = false, int oldhp = 0, std::vector<Skill::Type> oldskills = {});
	~StageState();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();
	void LoadWalls(std::string);
	void LoadPickups(std::string);
	void LoadPatrols(std::string);
private:
	std::string nextStage;
	TileSet* tileSet;
	Music music;
};

#endif