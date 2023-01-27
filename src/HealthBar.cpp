#include "HealthBar.h"
#include "Mushroom.h"
#include "Game.h"
#include "CameraFollower.h"

HealthBar::HealthBar(GameObject& associated, float iconSize) : Component(associated) {
	CameraFollower* newflwr=new CameraFollower(associated);
	associated.AddComponent(newflwr);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/Icon_life.png");
	newspr->SetScaleX((iconSize / associated.box.w), (iconSize / associated.box.h));
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