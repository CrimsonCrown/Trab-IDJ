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
#include "CooldownText.h"

CooldownText::CooldownText(GameObject& associated, Vec2 position, int index) : Component(associated) {
	this->index = index;
	this->position = position;
	CameraFollower* newflwr = new CameraFollower(associated, position.x, position.y);
	associated.AddComponent(newflwr);
	//cria text
	Text* newtxt = new Text((associated), "Recursos/font/Call me maybe.ttf", 30, Text::TextStyle::SOLID, "", { 255,255,255,255 });
	associated.AddComponent(newtxt);
	return;
}

void CooldownText::Update(float dt) {
	int newnum = ceil(Mushroom::player->GetSkill(index)->GetActiveCooldown());
	if (newnum >= 1) {
		((Text*)(associated.GetComponent("Text")))->SetText(std::to_string(newnum));
	}
	else {
		((Text*)(associated.GetComponent("Text")))->SetText("");
	}
	return;
}

void CooldownText::Render() {
	return;
}

bool CooldownText::Is(std::string type) {
	if (type == "CooldownText") {
		return true;
	}
	return false;
}