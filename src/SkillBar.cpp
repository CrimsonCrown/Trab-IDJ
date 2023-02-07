#include "SkillBar.h"
#include "Mushroom.h"
#include "Game.h"
#include "CameraFollower.h"
#include "SkillIcon.h"

SkillBar* SkillBar::bar;

SkillBar::SkillBar(GameObject& associated) : Component(associated) {
	bar=this;
	origin.x=0;
	origin.y=600-64;
	CameraFollower* newflwr=new CameraFollower(associated,origin.x,origin.y);
	associated.AddComponent(newflwr);
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/minion.png");
	newspr->SetRepeats(Mushroom::maxskills);
	newspr->SetScaleX((64/associated.box.w), (64 / associated.box.h));
	associated.AddComponent(newspr);
	return;
}

SkillBar::~SkillBar() {
	bar = nullptr;
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

void SkillBar::AddIcon(int index){
	Vec2 pos={origin.x+(index*64), origin.y};
	//pos.x=associated.box.x;
	//pos.y=associated.box.y;
	//Vec2 pos(0,0);
	GameObject* icon = new GameObject();
	SkillIcon* newicon = new SkillIcon((*icon), pos, index);
	icon->AddComponent(newicon);
	Game::GetInstance().GetCurrentState().AddObject(icon);
}