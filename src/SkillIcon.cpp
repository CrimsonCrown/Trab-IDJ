#include "Enemy.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "TileMover.h"
#include "TileChaser.h"
#include "Vision.h"
#include "SkillIcon.h"
#include "NavMap.h"
#include "Mushroom.h"
#include "CameraFollower.h"
#include "Text.h"
#include "ButtonText.h"
#include "CooldownText.h"

SkillIcon::SkillIcon(GameObject& associated, Vec2 position, int index) : Component(associated) {
	this->index=index;
	this->position=position;
	CameraFollower* newflwr=new CameraFollower(associated,position.x+8,position.y+7);
	associated.AddComponent(newflwr);
	//cria sprite
	Sprite* newspr = new Sprite((associated), Mushroom::player->GetSkill(index)->GetSprite());
	newspr->SetScaleX((50/associated.box.w), (50 / associated.box.h));
	associated.AddComponent(newspr);
	return;
}

void SkillIcon::Update(float dt) {
	return;
}

void SkillIcon::Render() {
	return;
}

bool SkillIcon::Is(std::string type) {
	if (type == "SkillIcon") {
		return true;
	}
	return false;
}

void SkillIcon::Start() {
	//cria text
	GameObject* buttontext = new GameObject();
	ButtonText* newtxt = new ButtonText((*buttontext), position.Add({7,7}), index);
	buttontext->AddComponent(newtxt);
	Game::GetInstance().GetCurrentState().AddObject(buttontext);
	//cria cooldown text
	GameObject* cooldowntext = new GameObject();
	CooldownText* newctxt = new CooldownText((*cooldowntext), position.Add({ associated.box.w-7, associated.box.h-8}), index);
	cooldowntext->AddComponent(newctxt);
	Game::GetInstance().GetCurrentState().AddObject(cooldowntext);
}