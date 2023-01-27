#include "Hearing.h"
#include "Game.h"
#include "Mushroom.h"
#include "AIModule.h"
#include "SightRay.h"
#include "Noise.h"
#include "Collider.h"

Hearing::Hearing(GameObject& associated, float sensibility) : Component(associated) {
	this->sensibility = sensibility;
	return;
}

void Hearing::Update(float dt) {
}

void Hearing::Render() {
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
		Vec2 position = ((Noise *) other.GetComponent("Noise"))->GetOrigin();
		float radius = ((Noise *) other.GetComponent("Noise"))->GetRadius();
		float dist = associated.box.Center().DistTo(position);
		if(dist <= sensibility*radius) {
			((AIModule*)associated.GetComponent("AIModule"))->Hear(position);
		}
	}
	return;
}