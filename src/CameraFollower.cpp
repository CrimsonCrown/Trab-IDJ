#include "CameraFollower.h"

CameraFollower::CameraFollower(GameObject& associated, float offsetx, float offsety) : Component(associated){
	this->offsetx=offsetx;
	this->offsety=offsety;
	return;
}

void CameraFollower::Update(float dt){
	associated.box.x=Camera::pos.x+offsetx;
	associated.box.y=Camera::pos.y+offsety;
	return;
}

void CameraFollower::Render(){
	Update(0);
	return;
}

bool CameraFollower::Is(std::string type){
	if(type=="CameraFollower"){
		return true;
	}
	return false;
}