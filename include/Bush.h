#ifndef BUSH_INCLUDE
#define BUSH_INCLUDE

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

class Bush : public Component {
public:
	Bush(GameObject& associated, TileCoords position, float tileSize, int sizex, int sizey);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	bool Ocupied();
private:
	TileCoords position;
	int sizex;
	int sizey;
	float tileSize;
};

#endif