#ifndef WALL_INCLUDE
#define WALL_INCLUDE

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

class Wall : public Component {
public:
	Wall(GameObject& associated, TileCoords origin, float tileSize, int sizex, int sizey);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
};

#endif