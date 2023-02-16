#ifndef TUTORIALSTATE_INCLUDE
#define TUTORIALSTATE_INCLUDE

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

class TutorialState : public State{
public:
	TutorialState(int page=1);
	~TutorialState();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();
	static const int maxpages = 3;
private:
	int page;
	std::string GetSprite();
	Music backgroundMusic;
};

#endif