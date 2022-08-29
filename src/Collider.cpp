#include "Collider.h"

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

void Collider::Render(){
	return;
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