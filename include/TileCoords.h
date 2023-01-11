#ifndef TILECOORDS_INCLUDE
#define TILECOORDS_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <cmath>
#include "Vec2.h"

class TileCoords{
public:
	TileCoords();
	TileCoords(int x, int y);
	TileCoords(Vec2 center, float tileSize);
	Vec2 Location(float tileSize);
	Vec2 Center(float tileSize);
	TileCoords Add(TileCoords coord);
	TileCoords Sub(TileCoords coord);
	int x;
	int y;
private:
};

#endif