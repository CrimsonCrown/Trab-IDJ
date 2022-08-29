#include "Collider.h"

//#define DEBUG
#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG
#define PI 3.1415926

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated){
	box=associated.box;
	this->scale=scale;
	this->offset=offset;
	return;
}

void Collider::Update(float dt){
	box=associated.box;
	box.w=box.w*scale.x;
	box.h=box.h*scale.y;
	box=box.Add((associated.box.Center().Add(offset)).Sub(box.Center()));
	return;
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.Center() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y).Sub(center)).Rotate( associated.angleDeg/(180/PI) ).Add(center.Sub(Camera::pos));
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y).Sub(center)).Rotate( associated.angleDeg/(180/PI) ).Add(center.Sub(Camera::pos));
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h).Sub(center)).Rotate( associated.angleDeg/(180/PI) ).Add(center.Sub(Camera::pos));
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h).Sub(center)).Rotate( associated.angleDeg/(180/PI) ).Add(center.Sub(Camera::pos));
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type){
	if(type=="Collider"){
		return true;
	}
	return false;
}

void Collider::SetScale(Vec2 scale){
	this->scale=scale;
	return;
}

void Collider::SetOffset(Vec2 offset){
	this->offset=offset;
	return;
}