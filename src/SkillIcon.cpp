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

SkillIcon::SkillIcon(GameObject& associated, Vec2 position, int index) : Component(associated) {
	this->index=index;
	this->position=position;
	CameraFollower* newflwr=new CameraFollower(associated,position.x,position.y);
	associated.AddComponent(newflwr);
	//cria sprite
	Sprite* newspr = new Sprite((associated), Mushroom::player->GetSkill(index)->GetSprite());
	newspr->SetScaleX((64/associated.box.w), (64 / associated.box.h));
	associated.AddComponent(newspr);
	//cria text
	//Text* newtxt=new Text((associated),"Recursos/font/Call me maybe.ttf", 30, Text::TextStyle::SOLID, "60", {255,255,255,255});
	//associated.AddComponent(newtxt);
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