#include "Enemy.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "TileChaser.h"
#include "Vision.h"

#define PI 3.1415926

Enemy::Enemy(GameObject& associated) : Component(associated) {
	Vision* newvision = new Vision((associated), 64, 3, PI/2);
	associated.AddComponent(newvision);
	TileChaser* newchaser = new TileChaser((associated), 64, 0.5);
	associated.AddComponent(newchaser);
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/alien.png");
	newspr->SetScaleX(0.43, 0.39);
	associated.AddComponent(newspr);
	//outros atributos
	dir = 0;
	hp = 30;
	return;
}

void Enemy::Start() {
	return;
}

void Enemy::Update(float dt) {
	return;
}

void Enemy::Render() {
	return;
}

bool Enemy::Is(std::string type) {
	if (type == "Mushroom") {
		return true;
	}
	return false;
}

void Enemy::NotifyCollision(GameObject& other) {
	if ((other.GetComponent("Bullet") != nullptr) && (((Bullet*)other.GetComponent("Bullet"))->targetsPlayer == true)) {
		hp -= 10;
		if (hp <= 0) {
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