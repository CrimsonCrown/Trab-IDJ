#include "Rat.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "TileChaser.h"
#include "Vision.h"
#include "AIModule.h"

#define PI 3.1415926

Rat::Rat(GameObject& associated, float tileSize, std::vector<PatrolCommand> commands) : Component(associated) {
	//cria sprite
	//Sprite* newspr = new Sprite((associated), "Recursos/img/Veado_transparente.png");
	Sprite* newspr = new Sprite((associated), "Recursos/img/rattrial.png", 4, 2, 1, 0, 1, 0, 0);
	newspr->SetScaleX((tileSize / associated.box.w), (tileSize / associated.box.h));
	associated.AddComponent(newspr);
	//AI
	AIModule*  newai = new AIModule((associated), tileSize);
	newai->AddPatrol(commands);
	newai->AddVision(1.1, (PI/2));
	newai->AddHearing(1);
	newai->AddChaser(2.1);
	newai->AddAnimations(2, "Recursos/animations/ratanims.txt");
	associated.AddComponent(newai);
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//outros atributos
	hp = 30;
	return;
}

void Rat::Start() {
	return;
}

void Rat::Update(float dt) {
	return;
}

void Rat::Render() {
	return;
}

bool Rat::Is(std::string type) {
	if (type == "Rat") {
		return true;
	}
	return false;
}

void Rat::NotifyCollision(GameObject& other) {
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