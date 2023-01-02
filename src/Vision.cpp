#include "Vision.h"
#include "Game.h"
#include "Mushroom.h"
#include "TileChaser.h"

Vision::Vision(GameObject& associated, float tileSize, float range, float angle) : Component(associated) {
	this->tileSize = tileSize;
	this->range = range;
	this->angle = angle;
	return;
}

void Vision::Update(float dt) {
	Vec2 dif = Mushroom::player->Position().Sub(associated.box.Center());
	if (dif.Magnitude() <= (range*tileSize)) {
		((TileChaser*)associated.GetComponent("TileChaser"))->See(Mushroom::player->Position());
	}
}

void Vision::Render() {
	return;
}

bool Vision::Is(std::string type) {
	if (type == "Vision") {
		return true;
	}
	return false;
}