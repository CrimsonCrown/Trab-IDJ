#include "Camera.h"

Vec2 Camera::pos={0,0};
Vec2 Camera::speed={0,0};
GameObject* Camera::focus;

void Camera::Follow(GameObject* newFocus){
	focus=newFocus;
}

void Camera::Unfollow(){
	focus=nullptr;
}

void Camera::Update(float dt){
	InputManager& input=InputManager::GetInstance();
	if(focus!=nullptr){
		pos.x=focus->box.x-(1024/2);
		pos.y=focus->box.y-(600/2);
	}
	else{
		speed.x=0;
		speed.y=0;
		if(input.IsKeyDown(LEFT_ARROW_KEY)){
			speed.x=-10;
		}
		if(input.IsKeyDown(RIGHT_ARROW_KEY)){
			speed.x=10;
		}
		if(input.IsKeyDown(UP_ARROW_KEY)){
			speed.y=-10;
		}
		if(input.IsKeyDown(DOWN_ARROW_KEY)){
			speed.y=10;
		}
		pos.x+=speed.x;
		pos.y+=speed.y;
	}
	return;
}