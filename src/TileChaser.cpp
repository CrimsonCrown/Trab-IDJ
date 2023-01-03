#include "TileChaser.h"
#include "Game.h"
#include "Mushroom.h"

TileChaser::TileChaser(GameObject& associated, float tileSize, float tileSpeed) : Component(associated) {
	this->tileSize = tileSize;
	this->tileSpeed = tileSpeed;
	state = RESTING;
	destinationType = LOST;
	return;
}

void TileChaser::Update(float dt) {
	if (state == RESTING) {
		if (destinationType == SIGHT || destinationType == HEARING || destinationType == SMELL || destinationType == PATROL) {
			Vec2 offset = { 0,0 };
			bool moved = false;
			nextPos = associated.box.Center();
			Vec2 dif = destination.Sub(nextPos);
			//alters offset
			if (dif.y < (-0.5*tileSize)) {
				offset.y -= tileSize;
				moved = true;
			}
			if (dif.y > (0.5*tileSize)) {
				offset.y += tileSize;
				moved = true;
			}
			if (dif.x < (-0.5*tileSize)) {
				offset.x -= tileSize;
				moved = true;
			}
			if (dif.x > (0.5*tileSize)) {
				offset.x += tileSize;
				moved = true;
			}
			if (moved) {
				state = MOVING;
				nextPos = nextPos.Add(offset);
			}
			else {
				destinationType = LOST;
			}
		}
	}
	if (state == MOVING) {
		Vec2 boxPos = associated.box.Center();
		float distToMove = tileSize * tileSpeed * dt;
		if (nextPos.DistTo(boxPos) <= distToMove) {
			associated.box.x = nextPos.x - (associated.box.w / 2);
			associated.box.y = nextPos.y - (associated.box.h / 2);
		}
		else {
			Vec2 speed = nextPos.Sub(boxPos).Normal().Mul(distToMove);
			associated.box = associated.box.Add(speed);
		}
		if (associated.box.Center().DistTo(nextPos) == 0) {
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

void TileChaser::See(Vec2 location) {
	destinationType = SIGHT;
	destination = location;
}

void TileChaser::Hear(Vec2 location) {
	if (destinationType != SIGHT) {
		destinationType = HEARING;
		destination = location;
	}
}

void TileChaser::Smell(Vec2 location) {
	if (destinationType != SIGHT && destinationType != HEARING) {
		destinationType = SMELL;
		destination = location;
	}
}

void TileChaser::Route(Vec2 location) {
	if (destinationType != SIGHT && destinationType != HEARING && destinationType != SMELL) {
		destinationType = PATROL;
		destination = location;
	}
}