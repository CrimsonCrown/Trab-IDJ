#include "Mushroom.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"

#define PI 3.1415926

Mushroom* Mushroom::player;

Mushroom::Mushroom(GameObject& associated) : Component(associated) {
	player = this;
	TileMover* newmover = new TileMover((associated), 64, 2);
	associated.AddComponent(newmover);
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/penguin.png");
	newspr->SetScaleX(0.55,1.12);
	associated.AddComponent(newspr);
	//outros atributos
	dir = 0;
	hp = 3;
	return;
}

Mushroom::~Mushroom() {
	player = nullptr;
	return;
}

void Mushroom::Start() {
	return;
}

void Mushroom::Update(float dt) {
	return;
}

void Mushroom::Render() {
	return;
}

bool Mushroom::Is(std::string type) {
	if (type == "Mushroom") {
		return true;
	}
	return false;
}

void Mushroom::NotifyCollision(GameObject& other) {
	if ((other.GetComponent("Bullet") != nullptr) && (((Bullet*)other.GetComponent("Bullet"))->targetsPlayer == true)) {
		hp -= 10;
		if (hp <= 0) {
			Camera::Unfollow();
			GameObject* explosion = new GameObject();
			Sprite* newspr = new Sprite((*explosion), "Recursos/img/penguindeath.png", 5, 0.4, 2);
			explosion->AddComponent(newspr);
			Sound* newsnd = new Sound((*explosion), "Recursos/audio/boom.wav");
			newsnd->Play();
			explosion->AddComponent(newsnd);
			explosion->box = explosion->box.Add(associated.box.Center().Sub(explosion->box.Center()));
			Game::GetInstance().GetCurrentState().AddObject(explosion);
			associated.RequestDelete();
		}
	}
	return;
}

Vec2 Mushroom::Position() {
	return associated.box.Center();
}

int Mushroom::GetHp(){
	return hp;
}