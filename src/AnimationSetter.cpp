#include "AnimationSetter.h"
#include "Game.h"
#include "Mushroom.h"
#include <fstream>

AnimationSetter::AnimationSetter(GameObject& associated, float tileSpeed, std::string name) : Component(associated) {
	LoadIndexes(name);
	this->tileSpeed=tileSpeed;
	SetIdleLeft();
}

void AnimationSetter::Update(float dt) {
	return;
}

void AnimationSetter::Render() {
	return;
}

bool AnimationSetter::Is(std::string type) {
	if (type == "AnimationSetter") {
		return true;
	}
	return false;
}

void AnimationSetter::SetIdle() {
	if (state2 != 0) {
		state2 = 0;
		frames = (indexes[state1][state2][1] - indexes[state1][state2][0])+1;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(indexes[state1][state2][0], indexes[state1][state2][1], 1.0 / (frames*tileSpeed));
	}
}

void AnimationSetter::SetIdleUp() {
	if (state1 != 0 || state2 != 0) {
		state1 = 0;
		state2 = 0;
		frames = (indexes[state1][state2][1] - indexes[state1][state2][0]) + 1;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(indexes[state1][state2][0], indexes[state1][state2][1], 1.0 / (frames*tileSpeed));
	}
}

void AnimationSetter::SetIdleDown() {
	if (state1 != 1 || state2 != 0) {
		state1 = 1;
		state2 = 0;
		frames = (indexes[state1][state2][1] - indexes[state1][state2][0]) + 1;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(indexes[state1][state2][0], indexes[state1][state2][1], 1.0 / (frames*tileSpeed));
	}
}

void AnimationSetter::SetIdleLeft(){
	if (state1 != 2 || state2 != 0) {
		state1 = 2;
		state2 = 0;
		frames = (indexes[state1][state2][1] - indexes[state1][state2][0])+1;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(indexes[state1][state2][0], indexes[state1][state2][1], 1.0 / (frames*tileSpeed));
	}
}

void AnimationSetter::SetIdleRight() {
	if (state1 != 3 || state2 != 0) {
		state1 = 3;
		state2 = 0;
		frames = (indexes[state1][state2][1] - indexes[state1][state2][0])+1;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(indexes[state1][state2][0], indexes[state1][state2][1], 1.0 / (frames*tileSpeed));
	}
}

void AnimationSetter::SetRunUp() {
	if (state1 != 0 || state2 != 1) {
		state1 = 0;
		state2 = 1;
		frames = (indexes[state1][state2][1] - indexes[state1][state2][0]) + 1;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(indexes[state1][state2][0], indexes[state1][state2][1], 1.0 / (frames*tileSpeed));
	}
}

void AnimationSetter::SetRunDown() {
	if (state1 != 1 || state2 != 1) {
		state1 = 1;
		state2 = 1;
		frames = (indexes[state1][state2][1] - indexes[state1][state2][0]) + 1;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(indexes[state1][state2][0], indexes[state1][state2][1], 1.0 / (frames*tileSpeed));
	}
}

void AnimationSetter::SetRunLeft(){
	if (state1 != 2 || state2 != 1) {
		state1 = 2;
		state2 = 1;
		frames = (indexes[state1][state2][1] - indexes[state1][state2][0])+1;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(indexes[state1][state2][0], indexes[state1][state2][1], 1.0 / (frames*tileSpeed));
	}
}

void AnimationSetter::SetRunRight() {
	if (state1 != 3 || state2 != 1) {
		state1 = 3;
		state2 = 1;
		frames = (indexes[state1][state2][1] - indexes[state1][state2][0])+1;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(indexes[state1][state2][0], indexes[state1][state2][1], 1.0 / (frames*tileSpeed));
	}
}

void AnimationSetter::UpdateSpeed(float newspeed) {
	tileSpeed = newspeed;
	((Sprite*)associated.GetComponent("Sprite"))->SetFrameTime(1.0 / (frames*tileSpeed));
}

void AnimationSetter::LoadIndexes(std::string name) {
	std::ifstream maptxt;
	char comma;
	maptxt.open(name);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				maptxt >> indexes[i][j][k] >> comma;
			}
		}
	}
	maptxt.close();
	return;
}