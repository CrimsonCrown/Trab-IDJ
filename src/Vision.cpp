#include "Vision.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"

Vision::Vision(GameObject& associated, float tileSize, float range, float angle) : Component(associated) {
	this->tileSize = tileSize;
	this->range = range;
	this->angle = angle;
	return;
}

void Vision::Update(float dt) {
	Vec2 dif = Mushroom::player->Position().Sub(associated.box.Center());
	if (dif.Magnitude() <= (range*tileSize)) {
		float direction = ((AIModule*)associated.GetComponent("AIModule"))->FacingDirection();
		float playerDirection = dif.Incline();
		//+2PI to remove negative values
		direction += 2 * PI;
		playerDirection += 2 * PI;
		if (playerDirection <= (direction + angle / 2) && playerDirection >= (direction - angle / 2)) {
			((AIModule*)associated.GetComponent("AIModule"))->See(Mushroom::player->Position());
		}
	}
}

void Vision::Render() {
#ifdef DEBUG
	const int np=9;
	float direction=((AIModule*)associated.GetComponent("AIModule"))->FacingDirection();
	SDL_Point points[np+2];

	Vec2 point = associated.box.Center().Sub(Camera::pos);
	points[0] = { (int)point.x, (int)point.y };
	points[np+1] = { (int)point.x, (int)point.y };

	for (int i = 0; i < np; i++) {
		point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate((direction - (angle / 2)) + (i*(angle/(np-1))))).Sub(Camera::pos);
		points[i+1] = { (int)point.x, (int)point.y };

	}

	/*point = associated.box.Center().Add(Vec2(tileSize*range,0).Rotate(direction)).Sub(Camera::pos);
	points[1] = { (int)point.x, (int)point.y };
	points[5] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate(direction+(angle/2))).Sub(Camera::pos);
	points[2] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*range, 0).Rotate(direction-(angle/2))).Sub(Camera::pos);
	points[4] = { (int)point.x, (int)point.y };*/

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, np+2);
#endif
	return;
}

bool Vision::Is(std::string type) {
	if (type == "Vision") {
		return true;
	}
	return false;
}