#include "AnimationSetter.h"
#include "Game.h"
#include "Mushroom.h"

AnimationSetter::AnimationSetter(GameObject& associated) : Component(associated) {
	state=0;
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

void AnimationSetter::SetIdle(){
	if(state!=0){
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(0,0,1);
		state=0;
	}
}

void AnimationSetter::SetRunLeft(){
	if(state!=1){
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(4,7,1);
		state=1;
	}
}