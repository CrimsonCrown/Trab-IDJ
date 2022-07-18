#ifndef TILESET_INCLUDE
#define TILESET_INCLUDE


#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include "Sprite.h"

class TileSet{
public:
	TileSet(int tileWidth, int tileHeight, std::string file);
	void RenderTile(int index, int x, int y);
	int GetTileWidth();
	int GetTileHeight();
private:
	Sprite tileSet;
	GameObject empty;
	int rows;
	int columns;
	int tileWidth;
	int tileHeight;
};

#endif