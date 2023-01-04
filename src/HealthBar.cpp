#include "HealthBar.h"
#include "Mushroom.h"
#include "Game.h"
#include "CameraFollower.h"

HealthBar::HealthBar(GameObject& associated) : Component(associated) {
	CameraFollower* newflwr=new CameraFollower(associated);
	associated.AddComponent(newflwr);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/hpheart.png");
	associated.AddComponent(newspr);
	return;
}

void HealthBar::Update(float dt) {
	if(Mushroom::player!=nullptr){
		((Sprite*)associated.GetComponent("Sprite"))->SetRepeats(Mushroom::player->GetHp());
	}
	return;
}

void HealthBar::Render() {
	return;
}

bool HealthBar::Is(std::string type) {
	if (type == "HealthBar") {
		return true;
	}
	return false;
}