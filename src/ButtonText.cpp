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

ButtonText::ButtonText(GameObject& associated, Vec2 position, int index) : Component(associated) {
	this->index = index;
	this->position = position;
	CameraFollower* newflwr = new CameraFollower(associated, position.x, position.y);
	associated.AddComponent(newflwr);
	//cria text
	Text* newtxt = new Text((associated), "Recursos/font/Call me maybe.ttf", 15, Text::TextStyle::SOLID, std::to_string(index + 1), { 255,255,255,255 });
	associated.AddComponent(newtxt);
	return;
}

void ButtonText::Update(float dt) {
	return;
}

void ButtonText::Render() {
	return;
}

bool ButtonText::Is(std::string type) {
	if (type == "ButtonText") {
		return true;
	}
	return false;
}