#include "Owl.h"
#include "Game.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileChaser.h"
#include "Vision.h"
#include "AIModule.h"

#define PI 3.1415926

Owl::Owl(GameObject& associated, float tileSize, std::vector<AngleCommand> commands) : Component(associated) {
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/coruja.png", 4, 1, 1, 0, 1, 0, 0);
	newspr->SetScaleX((tileSize / associated.box.w), (tileSize / associated.box.h));
	associated.AddComponent(newspr);
	//AI
	AIModule*  newai = new AIModule((associated), tileSize);
	newai->AddVision(1.1, (PI/2));
	newai->AddVisionPatrol(commands);
	newai->AddVisionChaser(1.2, 3*tileSize);
	newai->AddAnimations(2, "Recursos/animations/owlanims.txt");
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
