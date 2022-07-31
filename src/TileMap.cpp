#include "TileMap.h"
#include <fstream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated){
	//std::cout << "tried to make a map\n";
	Load(file);
	this->tileSet=tileSet;
	return;
}

void TileMap::Load(std::string file){
	std::ifstream maptxt;
	char comma;
	maptxt.open(file);
	maptxt >> mapWidth >> comma;
	maptxt >> mapHeight >> comma;
	maptxt >> mapDepth >> comma;
	//std::cout << mapWidth << " " << mapHeight << " " << mapDepth << "\n";
	tileMatrix.clear();
	int aux;
	int i;
	for(i=0;i<(mapWidth*mapHeight*mapDepth);i++){
		maptxt >> aux >> comma;
		aux--;
		//std::cout << aux << "\n";
		tileMatrix.push_back(aux);
	}
	maptxt.close();
	return;
}

void TileMap::SetTileSet(TileSet* tileSet){
	this->tileSet=tileSet;
	return;
}

int& TileMap::At(int x, int y, int z){
	return tileMatrix[x+(y*mapWidth)+(z*(mapHeight*mapWidth))];
}

void TileMap::Render(){
	int i;
	for(i=0;i<mapDepth;i++){
		RenderLayer(i,Camera::pos.x,Camera::pos.y);
	}
	return;
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
	int x;
	int y;
	for(x=0;x<mapWidth;x++){
		for(y=0;y<mapHeight;y++){
			tileSet->RenderTile(At(x,y,layer),associated.box.x+x*tileSet->GetTileWidth(),associated.box.y+y*tileSet->GetTileHeight());
		}
	}
	return;
}

int TileMap::GetWidth(){
	return mapWidth;
}

int TileMap::GetHeight(){
	return mapHeight;
}

int TileMap::GetDepth(){
	return mapDepth;
}

bool TileMap::Is(std::string type){
	if(type=="TileMap"){
		return true;
	}
	return false;
}