#include "SkillBar.h"
#include "Mushroom.h"
#include "Game.h"
#include "CameraFollower.h"

SkillBar* SkillBar::bar;

SkillBar::SkillBar(GameObject& associated) : Component(associated) {
	bar=this;
	CameraFollower* newflwr=new CameraFollower(associated,(1024-(64*Mushroom::maxskills))/2,576-64);
	associated.AddComponent(newflwr);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/minion.png");
	newspr->SetRepeats(Mushroom::maxskills);
	newspr->SetScaleX((64/associated.box.w), (64 / associated.box.h));
	associated.AddComponent(newspr);
	return;
}

void SkillBar::Update(float dt) {
	return;
}

void SkillBar::Render() {
	return;
}

bool SkillBar::Is(std::string type) {
	if (type == "SkillBar") {
		return true;
	}
	return false;
}