#include "AIModule.h"
#include "Vision.h"
#include "Game.h"
#include "Mushroom.h"
#include "TileChaser.h"
#include "Patrol.h"

AIModule::AIModule(GameObject& associated, float tileSize, float facingDirection) : Component(associated) {
	this->tileSize = tileSize;
	this->facingDirection = facingDirection;
	vision = false;
	chaser = false;
	patrol = false;
	return;
}

void AIModule::Update(float dt) {
	return;
}

void AIModule::Render() {
	return;
}

bool AIModule::Is(std::string type) {
	if (type == "AIModule") {
		return true;
	}
	return false;
}

void AIModule::AddVision(float range, float angle) {
	if (vision == false) {
		vision = true;
		Vision* newvision = new Vision((associated), tileSize, range, angle);
		associated.AddComponent(newvision);
	}
}

void AIModule::AddChaser(float tileSpeed) {
	if (chaser == false) {
		chaser = true;
		TileChaser* newchaser = new TileChaser((associated), tileSize, tileSpeed);
		associated.AddComponent(newchaser);
	}
}

void AIModule::AddPatrol(std::queue<Vec2> route) {
	if (patrol == false) {
		patrol = true;
		Patrol* newpatrol = new Patrol((associated), route);
		associated.AddComponent(newpatrol);
	}
}

void AIModule::See(Vec2 location) {
	if (chaser == true) {
		((TileChaser*)associated.GetComponent("TileChaser"))->See(location);
	}
}

void AIModule::Hear(Vec2 location) {
	if (chaser == true) {
		((TileChaser*)associated.GetComponent("TileChaser"))->Hear(location);
	}
}

void AIModule::Smell(Vec2 location) {
	if (chaser == true) {
		((TileChaser*)associated.GetComponent("TileChaser"))->Smell(location);
	}
}

void AIModule::Route(Vec2 location) {
	if (chaser == true) {
		((TileChaser*)associated.GetComponent("TileChaser"))->Route(location);
	}
}

float AIModule::FacingDirection() {
	return facingDirection;
}

void AIModule::ChangeDirection(float newdir) {
	facingDirection = newdir;
}