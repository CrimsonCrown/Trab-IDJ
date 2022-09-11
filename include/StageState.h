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

class StageState : public State{
public:
	StageState();
	~StageState();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();
private:
	TileSet* tileSet;
	Music music;
};

#endif