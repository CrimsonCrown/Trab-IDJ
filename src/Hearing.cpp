#include "Hearing.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"
#include "SightRay.h"
#include "Noise.h"
#include "Collider.h"

Hearing::Hearing(GameObject& associated, float radius) : Component(associated) {
	this->radius = radius;
	waitingCollision=false;
    position=Vec2(0,0);
	associated.box.x=(associated.box.x + associated.box.w/2)-radius;
	associated.box.y=(associated.box.y + associated.box.h/2)-radius;
    associated.box.w=radius*2;
	associated.box.h=radius*2;
	return;
}

void Hearing::Update(float dt) {
	if(waitingCollision){
		waitingCollision=false;
		((AIModule*)associated.GetComponent("AIModule"))->Hear(position);
	}
}

void Hearing::Render() {
#ifdef DEBUG
	const int np=24;
    float direction = 0;
	SDL_Point points[np];

	for (int i = 0; i < np; i++) {
		Vec2 point = associated.box.Center().Add(Vec2(radius, 0).Rotate((direction - PI) + (i*((2*PI)/(np-1))))).Sub(Camera::pos);
		points[i] = { (int)point.x, (int)point.y };

	}

	/*point = associated.box.Center().Add(Vec2(tileSize*radius,0).Rotate(direction)).Sub(Camera::pos);
	points[1] = { (int)point.x, (int)point.y };
	points[5] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*radius, 0).Rotate(direction+(angle/2))).Sub(Camera::pos);
	points[2] = { (int)point.x, (int)point.y };

	point = associated.box.Center().Add(Vec2(tileSize*radius, 0).Rotate(direction-(angle/2))).Sub(Camera::pos);
	points[4] = { (int)point.x, (int)point.y };*/

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, np);
#endif
	return;
}

bool Hearing::Is(std::string type) {
	if (type == "Hearing") {
		return true;
	}
	return false;
}

void Hearing::NotifyCollision(GameObject& other){
	if(other.GetComponent("Noise")!=nullptr){
		waitingCollision = true;
		position = Vec2(associated.box.x, associated.box.y);
		float angle = ((Noise *) other.GetComponent("Noise"))->GetOrigin().Incline(position);
		position = position.Add(Vec2(radius * cos(angle), radius * sin(angle)));
	}
	return;
}