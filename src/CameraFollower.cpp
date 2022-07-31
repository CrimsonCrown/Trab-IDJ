#include "CameraFollower.h"

CameraFollower::CameraFollower(GameObject& associated) : Component(associated){
	return;
}

void CameraFollower::Update(float dt){
	associated.box.x=Camera::pos.x;
	associated.box.y=Camera::pos.y;
	return;
}

void CameraFollower::Render(){
	return;
}

bool CameraFollower::Is(std::string type){
	if(type=="CameraFollower"){
		return true;
	}
	return false;
}