#include "TileChaser.h"
#include "Game.h"
#include "Mushroom.h"

TileChaser::TileChaser(GameObject& associated, float tileSize, float tileSpeed) : Component(associated) {
	this->tileSize = tileSize;
	this->tileSpeed = tileSpeed;
	state = RESTING;
	return;
}

void TileChaser::Update(float dt) {
	if (state == RESTING) {
		Vec2 offset = { 0,0 };
		bool moved = false;
		destination = associated.box.Center();
		Vec2 dif = Mushroom::player->Position().Sub(destination);
		//alters offset
		if (dif.y<(-0.5*tileSize)) {
			offset.y -= tileSize;
			moved = true;
		}
		if (dif.y>(0.5*tileSize)) {
			offset.y += tileSize;
			moved = true;
		}
		if (dif.x<(-0.5*tileSize)) {
			offset.x -= tileSize;
			moved = true;
		}
		if (dif.x>(0.5*tileSize)) {
			offset.x += tileSize;
			moved = true;
		}
		if (moved) {
			state = MOVING;
			destination = destination.Add(offset);
		}
	}
	if (state == MOVING) {
		Vec2 boxPos = associated.box.Center();
		float distToMove = tileSize * tileSpeed * dt;
		if (destination.DistTo(boxPos) <= distToMove) {
			associated.box.x = destination.x - (associated.box.w / 2);
			associated.box.y = destination.y - (associated.box.h / 2);
		}
		else {
			Vec2 speed = destination.Sub(boxPos).Normal().Mul(distToMove);
			associated.box = associated.box.Add(speed);
		}
		if (associated.box.Center().DistTo(destination) == 0) {
			state = RESTING;
		}
	}
	return;
}

void TileChaser::Render() {
	return;
}

bool TileChaser::Is(std::string type) {
	if (type == "TileChaser") {
		return true;
	}
	return false;
}