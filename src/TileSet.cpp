#include "TileSet.h"


TileSet::TileSet(int tileWidth, int tileHeight, std::string file) : tileSet(empty, file.c_str()){
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	//std::cout <<"tried to make a set\n";
	if(tileSet.IsOpen()){
		rows=tileSet.GetHeight()/this->tileHeight;
		columns=tileSet.GetWidth()/this->tileWidth;
	}
	else{
		std::cout << SDL_GetError();;
	}
	//std::cout << columns << " " << rows << "\n";
}

void TileSet::RenderTile(int index, int x, int y){
	if(index>=0&&index<=((columns*rows)-1)){
		int row;
		int column;
		column=index%columns;
		row=index/columns;
		tileSet.SetClip(column*tileWidth, row*tileHeight, tileWidth, tileHeight);
		//std::cout << "(" << column*tileWidth << " " << row*tileHeight << " " << tileWidth << " " << tileHeight << "\n";
		tileSet.Render(x,y,tileWidth,tileHeight);
	}
}

int TileSet::GetTileWidth(){
	return tileWidth;
}

int TileSet::GetTileHeight(){
	return tileHeight;
}