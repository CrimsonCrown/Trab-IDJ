#include "Owl.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "TileChaser.h"
#include "Vision.h"
#include "AIModule.h"

#define PI 3.1415926

Owl::Owl(GameObject& associated, float tileSize, std::vector<PatrolCommand> commands) : Component(associated) {
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/coruja.png", 4, 4, 1, 0, 1, 0, 0);
	newspr->SetScaleX((tileSize / associated.box.w), (tileSize / associated.box.h));
	associated.AddComponent(newspr);
	//AI
	AIModule*  newai = new AIModule((associated), tileSize);
	newai->AddVision(1.1, (PI/2));
	newai->AddAnimations(2, "Recursos/animations/keyframes_coruja_copiar.txt");
	associated.AddComponent(newai);
	Collider* newcol = new Collider((associated));
	associated.AddComponent(newcol);
	//outros atributos
	return;
}

void Owl::Start() {
	return;
}

void Owl::Update(float dt) {
	return;
}

void Owl::Render() {
	return;
}

bool Owl::Is(std::string type) {
	if (type == "Owl") {
		return true;
	}
	return false;
}

void Owl::NotifyCollision(GameObject& other) {
	if ((other.GetComponent("Bullet") != nullptr) && (((Bullet*)other.GetComponent("Bullet"))->targetsPlayer == true)) {
		// hp -= 10;
		// if (hp <= 0) {
		// 	GameObject* explosion = new GameObject();
		// 	Sprite* newspr = new Sprite((*explosion), "Recursos/img/penguindeath.png", 5, 0.4, 2);
		// 	explosion->AddComponent(newspr);
		// 	Sound* newsnd = new Sound((*explosion), "Recursos/audio/boom.wav");
		// 	newsnd->Play();
		// 	explosion->AddComponent(newsnd);
		// 	explosion->box = explosion->box.Add(associated.box.Center().Sub(explosion->box.Center()));
		// 	Game::GetInstance().GetCurrentState().AddObject(explosion);
		// 	associated.RequestDelete();
		// }
	}
	return;
}