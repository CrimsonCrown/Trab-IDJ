#include "TileCoords.h"

TileCoords::TileCoords(){
	x=0;
	y=0;
	return;
}

TileCoords::TileCoords(int x, int y){
	this->x=x;
	this->y=y;
	return;
}

TileCoords::TileCoords(Vec2 center, float tileSize){
	Vec2 result=center;
	result.x-=tileSize/2;
	result.y-=tileSize/2;
	result=result.Mul(1.0/tileSize);
	x=round(result.x);
	y=round(result.y);
}

Vec2 TileCoords::Location(float tileSize){
	Vec2 result;
	result.x=tileSize*x;
	result.y=tileSize*y;
	return result;
}

Vec2 TileCoords::Center(float tileSize){
	Vec2 result;
	result.x=tileSize*(x+0.5);
	result.y=tileSize*(y+0.5);
	return result;
}

TileCoords TileCoords::Add(TileCoords coord){
	TileCoords result;
	result.x=x+coord.x;
	result.y=y+coord.y;
	return result;
}

TileCoords TileCoords::Sub(TileCoords coord){
	TileCoords result;
	result.x=x-coord.x;
	result.y=y-coord.y;
	return result;
}