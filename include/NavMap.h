#ifndef NAVMAP_INCLUDE
#define NAVMAP_INCLUDE

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

class NavMap : public Component {
public:
	NavMap(GameObject& associated, float tileSize, int x, int y);
	~NavMap();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Fill(TileCoords origin, int x, int y);
	static NavMap* map;
private:
	int Index(int x, int y);
	bool At(int x, int y);
	std::vector<bool> mapVacancy;
	float tileSize;
	int xsize;
	int ysize;
};

#endif