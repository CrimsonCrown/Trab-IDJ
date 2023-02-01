#include "Enemy.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "TileChaser.h"
#include "Vision.h"
#include "AIModule.h"

#define PI 3.1415926

Enemy::Enemy(GameObject& associated, float tileSize, std::vector<PatrolCommand> commands) : Component(associated) {
	AIModule*  newai = new AIModule((associated), tileSize);
	newai->AddPatrol(commands);
	newai->AddVision(3.1, (PI/3)*2);
	newai->AddHearing(0.5);
	newai->AddChaser(2);
	associated.AddComponent(newai);
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//cria sprite
	//Sprite* newspr = new Sprite((associated), "Recursos/img/Veado_transparente.png");
	Sprite* newspr = new Sprite((associated), "Recursos/img/deertrial.png", 3, 1, 1.0 / 6.0, 0, 1, 0, 2);
	newspr->SetScaleX((tileSize/associated.box.w), (tileSize / associated.box.h));
	associated.AddComponent(newspr);
	//outros atributos
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
	if (type == "Enemy") {
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