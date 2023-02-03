#include "TileChaser.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"
#include "NavMap.h"

TileChaser::TileChaser(GameObject& associated, float tileSize, float tileSpeed) : Component(associated) {
	this->tileSize = tileSize;
	this->tileSpeed = tileSpeed;
	state = RESTING;
	destinationType = LOST;
	needspath = true;
	return;
}

void TileChaser::Update(float dt) {
	if (state == RESTING) {
		if (destinationType == SIGHT || destinationType == HEARING || destinationType == SMELL || destinationType == PATROL) {
			if (needspath) {
				//std::cout << "needs a path\n";
				NavMap::map->Path(TileCoords(associated.box.Center(), tileSize), destination, path);
				needspath = false;
			}
			if (path.empty()) {
				destinationType = LOST;
				((AIModule*)associated.GetComponent("AIModule"))->Stop();
				//std::cout << "no path yet\n";
			}
			else {
				//std::cout << "we have path yet\n";
				state = MOVING;
				nextPos = path.front();
				path.pop_front();
				Vec2 offset = nextPos.Center(tileSize).Sub(associated.box.Center());
				((AIModule*)associated.GetComponent("AIModule"))->ChangeDirection(offset.Incline());
			}
			/*
			bool moved = false;
			Vec2 offset={0,0};
			nextPos = TileCoords(associated.box.Center(), tileSize);
			TileCoords dif = destination.Sub(nextPos);
			//alters offset
			if (dif.y <= -1) {
				nextPos.y -= 1;
				offset.y-=1;
				moved = true;
			}
			if (dif.y >= 1) {
				nextPos.y += 1;
				offset.y+=1;
				moved = true;
			}
			if (dif.x <= -1) {
				nextPos.x -= 1;
				offset.x-=1;
				moved = true;
			}
			if (dif.x >= 1) {
				nextPos.x += 1;
				offset.x+=1;
				moved = true;
			}
			if (moved) {
				state = MOVING;
				((AIModule*)associated.GetComponent("AIModule"))->ChangeDirection(offset.Incline());
			}
			else {
				destinationType = LOST;
			}*/
		}
	}
	if (state == MOVING) {
		Vec2 boxPos = associated.box.Center();
		float distToMove = tileSize * tileSpeed * dt;
		if (nextPos.Center(tileSize).DistTo(boxPos) <= distToMove) {
			associated.box.x = nextPos.Center(tileSize).x - (associated.box.w / 2);
			associated.box.y = nextPos.Center(tileSize).y - (associated.box.h / 2);
		}
		else {
			Vec2 speed = nextPos.Center(tileSize).Sub(boxPos).Normal().Mul(distToMove);
			associated.box = associated.box.Add(speed);
		}
		if (associated.box.Center().DistTo(nextPos.Center(tileSize)) == 0) {
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

void TileChaser::See(TileCoords location) {
	destinationType = SIGHT;
	destination = location;
	needspath = true;
}

void TileChaser::Hear(TileCoords location) {
	if (destinationType != SIGHT) {
		destinationType = HEARING;
		destination = location;
		needspath = true;
	}
}

void TileChaser::Smell(TileCoords location) {
	if (destinationType != SIGHT && destinationType != HEARING) {
		destinationType = SMELL;
		destination = location;
		needspath = true;
	}
}

void TileChaser::Route(TileCoords location) {
	if (destinationType != SIGHT && destinationType != HEARING && destinationType != SMELL) {
		if(destinationType == PATROL){
			if(destination.x!=location.x||destination.y!=location.y){
				destinationType = PATROL;
				destination = location;
				needspath = true;
			}
		}
		else{
			destinationType = PATROL;
			destination = location;
			needspath = true;
		}
	}
}