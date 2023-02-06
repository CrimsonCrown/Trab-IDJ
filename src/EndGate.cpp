#include "Mushroom.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "AnimationSetter.h"
#include "Pickup.h"
#include "SkillBar.h"
#include "Skill.h"
#include "EndGate.h"

#define PI 3.1415926

bool EndGate::ending;

EndGate::EndGate(GameObject& associated, float tileSize, TileCoords initialPosition) : Component(associated) {
	ending = false;
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/choromelo.png", 1, 1);
	newspr->SetScaleX((tileSize/associated.box.w), (tileSize / associated.box.h));
	associated.AddComponent(newspr);
	//cria alterador de sprites
	//outros atributos
	this->tileSize = tileSize;
	Place(initialPosition);
	return;
}

EndGate::~EndGate() {
	ending=false;
	return;
}

void EndGate::Update(float dt) {
	return;
}

void EndGate::Render() {
	return;
}

bool EndGate::Is(std::string type) {
	if (type == "EndGate") {
		return true;
	}
	return false;
}

void EndGate::NotifyCollision(GameObject& other) {
	if (other.GetComponent("Mushroom") != nullptr&&other.box.CenterDist(associated.box)<0.5*tileSize) {
		ending = true;
	}
	return;
}
void EndGate::Place(TileCoords position){
	Vec2 location=position.Location(tileSize);
	associated.box.x=location.x;
	associated.box.y=location.y;
}