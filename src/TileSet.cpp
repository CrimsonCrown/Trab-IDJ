#include "TileSet.h"


TileSet::TileSet(int tileWidth, int tileHeight, std::string file) : tileSet(empty, file.c_str()){
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	if(tileSet.IsOpen()){
		columns=tileSet.GetHeight()/this->tileHeight;
		rows=tileSet.GetWidth()/this->tileWidth;
	}
	else{
		std::cout << SDL_GetError();;
	}
}

void TileSet::RenderTile(unsigned int index, int x, int y){
	if(index<=((columns*rows)-1)){
		int row;
		int column;
		column=index%columns;
		row=index/columns;
		tileSet.SetClip(column*tileWidth, row*tileHeight, tileWidth, tileHeight);
		tileSet.Render(x,y,tileWidth,tileHeight);
	}
}

int TileSet::GetTileWidth(){
	return tileWidth;
}

int TileSet::GetTileHeight(){
	return tileHeight;
}