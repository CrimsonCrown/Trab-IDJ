#include "TileChaser.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"

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
				((AIModule*)associated.GetComponent("AIModule"))->ChangeDirection(offset.Incline());
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
#ifdef DEBUG
	SDL_Point points[6];

	Vec2 point = associated.box.Center().Sub(Camera::pos);
	points[0] = { (int)point.x, (int)point.y };

	point.x+=64;
	points[1] = { (int)point.x, (int)point.y };
	points[5] = { (int)point.x, (int)point.y };

	point.x-=64;
	point.y+=64;
	points[2] = { (int)point.x, (int)point.y };

	point.x-=64;
	point.y-=64;
	points[3] = { (int)point.x, (int)point.y };

	point.x+=64;
	point.y-=64;
	points[4] = { (int)point.x, (int)point.y };

	/*point = associated.box.Center().Add(Vec2(tileSize*range,0).Rotate(direction)).Sub(Camera::pos);
	points[1] = { (int)point.x, (int)point.y };
	points[5] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate(direction+(angle/2))).Sub(Camera::pos);
	points[2] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate(direction-(angle/2))).Sub(Camera::pos);
	points[4] = { (int)point.x, (int)point.y };*/
	int colorR;
	int colorG;
	int colorB;
	if(destinationType==SIGHT){
		colorR=255;
		colorG=0;
		colorB=0;
	}
	else if(destinationType==PATROL){
		colorR=0;
		colorG=255;
		colorB=0;
	}
	else{
		colorR=0;
		colorG=0;
		colorB=255;
	}

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 6);
#endif
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