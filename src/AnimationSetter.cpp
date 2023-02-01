#include "AnimationSetter.h"
#include "Game.h"
#include "Mushroom.h"

AnimationSetter::AnimationSetter(GameObject& associated, float tileSpeed) : Component(associated) {
	state=0;
	frames = 1;
	this->tileSpeed=tileSpeed;
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
		frames=1;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(0,0,1.0/(frames*tileSpeed));
		state=0;
	}
}

void AnimationSetter::SetRunLeft(){
	if(state!=1){
		frames = 4;
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(4,7, 1.0 / (frames*tileSpeed));
		state=1;
	}
}

void AnimationSetter::UpdateSpeed(float newspeed) {
	tileSpeed = newspeed;
	((Sprite*)associated.GetComponent("Sprite"))->SetFrameTime(1.0 / (frames*tileSpeed));
}