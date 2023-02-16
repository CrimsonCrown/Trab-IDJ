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
	Sprite* newspr = new Sprite((associated), "Recursos/img/Saida.png", 1, 1);
	newspr->SetScaleX((tileSize/associated.box.w), (tileSize / associated.box.h));
	associated.AddComponent(newspr);
	//cria alterador de sprites
	//outros atributos
	this->tileSize = tileSize;
	Place(initialPosition);
	endset = false;
	return;
}

EndGate::~EndGate() {
	ending=false;
	return;
}

void EndGate::Update(float dt) {
	endTimer.Update(dt);
	if (endset) {
		if (endTimer.Get() >= 1) {
			ending = true;
		}
	}
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
		if (!endset) {
			endset = true;
			endTimer.Restart();
			//sprite de pular no buraco
			GameObject* explosion = new GameObject();
			Sprite* newspr = new Sprite((*explosion), "Recursos/img/Certo_Entrando_buraco.png", 4, 3, 1.0 / 5.0, 2, 1, 0, 4);
			newspr->SetScaleX((tileSize / explosion->box.w), (tileSize / explosion->box.h));
			explosion->AddComponent(newspr);
			explosion->box = explosion->box.Add(associated.box.Center().Sub(explosion->box.Center()));
			Game::GetInstance().GetCurrentState().AddObject(explosion);
		}
	}
	return;
}
void EndGate::Place(TileCoords position){
	Vec2 location=position.Location(tileSize);
	associated.box.x=location.x;
	associated.box.y=location.y;
}