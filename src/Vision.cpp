#include "Vision.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"
#include "SightRay.h"

Vision::Vision(GameObject& associated, float tileSize, float range, float angle) : Component(associated) {
	this->tileSize = tileSize;
	this->range = range;
	this->angle = angle;
	waitingCollision=false;
	seeing=false;
	return;
}

void Vision::Update(float dt) {
	Vec2 dif = Mushroom::player->Position().Sub(associated.box.Center());
	seeing=false;
	if(waitingCollision){
		waitingCollision=false;
		((AIModule*)associated.GetComponent("AIModule"))->See(positionSeen);
		seeing=true;
	}
	if (dif.Magnitude() <= (range*tileSize)) {
		float direction = ((AIModule*)associated.GetComponent("AIModule"))->FacingDirection();
		float playerDirection = dif.Incline();
		if (direction < 0) {
			direction += 2*PI;
		}
		if (playerDirection < 0) {
			playerDirection += 2*PI;
		}
		float upperBound = direction + angle / 2;
		float lowerBound = direction - angle / 2;
		//+2PI to remove negative values
		if (lowerBound < 0) {
			lowerBound += 2 * PI;
			if (playerDirection >= lowerBound || playerDirection <= upperBound) {
				waitingCollision=true;
			}
		}
		else if (upperBound > (2 * PI)) {
			upperBound -= 2 * PI;
			if (playerDirection >= lowerBound || playerDirection <= upperBound) {
				waitingCollision=true;
			}
		}
		else if (playerDirection <= upperBound && playerDirection >= lowerBound) {
				waitingCollision=true;
		}
	}
	if(waitingCollision){
		//cria raio
		positionSeen=Mushroom::player->Position();
		GameObject* ray=new GameObject();
		SightRay* newray=new SightRay((*ray), (*this), associated.box.Center(), positionSeen, tileSize/2, seeing);
		ray->AddComponent(newray);
		Game::GetInstance().GetCurrentState().AddObject(ray);
	}
}

void Vision::Render() {
#ifdef DEBUG
	const int np=15;
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

void Vision::Blocked(){
	waitingCollision=false;
}