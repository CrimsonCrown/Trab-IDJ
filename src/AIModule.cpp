#include "AIModule.h"
#include "Vision.h"
#include "Game.h"
#include "Mushroom.h"
#include "TileChaser.h"
#include "PatrolSchedule.h"
#include "Hearing.h"
#include "AnimationSetter.h"
#include "HearingView.h"

AIModule::AIModule(GameObject& associated, float tileSize, float facingDirection) : Component(associated) {
	this->tileSize = tileSize;
	this->facingDirection = facingDirection;
	vision = false;
	chaser = false;
	patrol = false;
	hearing = false;
	animations = false;
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

void AIModule::AddPatrol(std::vector<PatrolCommand> commands) {
	if (patrol == false) {
		patrol = true;
		PatrolSchedule* newpatrol = new PatrolSchedule((associated), tileSize, commands);
		associated.AddComponent(newpatrol);
	}
}

void AIModule::AddHearing(float radius) {
	if (hearing == false) {
		hearing = true;
		Hearing* newhearing = new Hearing((associated), radius);
		associated.AddComponent(newhearing);
	}
}

void AIModule::AddAnimations(float tileSpeed, std::string name) {
	if (animations == false) {
		animations = true;
		AnimationSetter* newanims = new AnimationSetter((associated), tileSpeed, name);
		associated.AddComponent(newanims);
	}
}

void AIModule::See(Vec2 location) {
	if (chaser == true) {
		((TileChaser*)associated.GetComponent("TileChaser"))->See(TileCoords(location, tileSize));
	}
}

void AIModule::Hear(Vec2 location) {
	if (chaser == true) {
		((TileChaser*)associated.GetComponent("TileChaser"))->Hear(TileCoords(location, tileSize));
	}
}

void AIModule::Smell(Vec2 location) {
	if (chaser == true) {
		((TileChaser*)associated.GetComponent("TileChaser"))->Smell(TileCoords(location, tileSize));
	}
}

void AIModule::Route(TileCoords location) {
	if (chaser == true) {
		((TileChaser*)associated.GetComponent("TileChaser"))->Route(location);
	}
}

float AIModule::FacingDirection() {
	return facingDirection;
}

void AIModule::ChangeDirection(float newdir, bool moving) {
	facingDirection = newdir;
	if (animations) {
		if (facingDirection < 0) {
			facingDirection += 2*PI;
		}
		else if (facingDirection > 2 * PI) {
			facingDirection -= 2 * PI;
		}
		if (facingDirection > 13 * (PI / 8) || facingDirection < 3 * (PI / 8)) {
			//direita
			if (moving) {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetRunRight();
			}
			else {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetIdleRight();
			}
		}
		else if (facingDirection > 5 * (PI / 8) && facingDirection < 11 * (PI / 8)) {
			//esquerda
			if (moving) {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetRunLeft();
			}
			else {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetIdleLeft();
			}
		}
		else if (facingDirection > 3 * (PI / 8) && facingDirection < 5 * (PI / 8)) {
			//baixo
			if (moving) {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetRunDown();
			}
			else {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetIdleDown();
			}
		}
		else if (facingDirection > 11 * (PI / 8) && facingDirection < 13 * (PI / 8)) {
			//cima
			if (moving) {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetRunUp();
			}
			else {
				((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetIdleUp();
			}
		}
	}
	//facingDirection = newdir;
}

void AIModule::ShiftDirection(float newdir, bool moving) {
	ChangeDirection(facingDirection + newdir, moving);
}

void AIModule::Stop() {
	if (animations) {
		((AnimationSetter*)associated.GetComponent("AnimationSetter"))->SetIdle();
	}
}
void AIModule::Spooked() {
	if (hearing) {
		((HearingView*)((Hearing*)associated.GetComponent("Hearing"))->GetViewer().lock()->GetComponent("HearingView"))->Play();
	}
}