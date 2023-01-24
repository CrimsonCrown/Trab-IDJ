#include "Enemy.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "TileChaser.h"
#include "Vision.h"
#include "Wall.h"
#include "NavMap.h"

#define PI 3.1415926

Wall::Wall(GameObject& associated, TileCoords origin, float tileSize, int sizex, int sizey, std::string imgFile) : Component(associated) {
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//cria sprite
	Sprite* newspr = new Sprite((associated), imgFile);
	newspr->SetScaleX((tileSize/associated.box.w)*sizex, (tileSize / associated.box.h)*sizey);
	associated.AddComponent(newspr);
	//fill map and place
	NavMap::map->Fill(origin, sizex, sizey);
	associated.box.x = origin.Location(tileSize).x;
	associated.box.y = origin.Location(tileSize).y;
	return;
}

void Wall::Update(float dt) {
	return;
}

void Wall::Render() {
	return;
}

bool Wall::Is(std::string type) {
	if (type == "Wall") {
		return true;
	}
	return false;
}