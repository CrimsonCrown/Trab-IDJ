#ifndef SKILLICON_INCLUDE
#define SKILLICON_INCLUDE

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
#include "TileCoords.h"

class SkillIcon : public Component {
public:
	SkillIcon(GameObject& associated, Vec2 position, int index);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Start();
private:
	Vec2 position;
	int index;
};

#endif