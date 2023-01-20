#include "Enemy.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "TileChaser.h"
#include "Vision.h"
#include "Bush.h"
#include "NavMap.h"
#include "Mushroom.h"

#define PI 3.1415926

Bush::Bush(GameObject& associated, TileCoords position, float tileSize, int sizex, int sizey) : Component(associated) {
	this->tileSize=tileSize;
	this->position=position;
	this->sizex=sizex;
	this->sizey=sizey;
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/moita1.png");
	newspr->SetScaleX((tileSize/associated.box.w)*sizex, (tileSize / associated.box.h)*sizey);
	associated.AddComponent(newspr);
	associated.box.x = position.Location(tileSize).x;
	associated.box.y = position.Location(tileSize).y;
	return;
}

void Bush::Update(float dt) {
	return;
}

void Bush::Render() {
	return;
}

bool Bush::Is(std::string type) {
	if (type == "Bush") {
		return true;
	}
	return false;
}

bool Bush::Ocupied(){
	TileCoords playercoords(Mushroom::player->Position(), tileSize);
	if(playercoords.x<position.x||playercoords.x>=position.x+sizex||playercoords.y<position.y||playercoords.y>=position.y+sizey){
		return false;
	}
	return true;
}