#include "Face.h"

Face::Face(GameObject& associated) : Component(associated){
	hitpoints=30;
	return;
}

void Face::Damage(int damage){
	hitpoints-=damage;
	if(hitpoints<=0){
		associated.RequestDelete();
	}
	((Sound*)associated.GetComponent("Sound"))->Play();
	return;
}

void Face::Update(float dt){
	if(InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT)){
		if(associated.box.Contains({(float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY()})){
			Damage(std::rand() % 10 + 10);
		}
	}
	return;
}

void Face::Render(){
	return;
}

bool Face::Is(std::string type){
	if(type=="Face"){
		return true;
	}
	return false;
}