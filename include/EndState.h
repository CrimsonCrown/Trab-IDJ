#ifndef ENDSTATE_INCLUDE
#define ENDSTATE_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

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

class EndState : public State{
public:
	EndState();
	~EndState();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();
private:
	Music backgroundMusic;
};

#endif