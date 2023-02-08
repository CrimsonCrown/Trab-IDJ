#include "Skill.h"
#include "Game.h"
#include "Collider.h"
#include "Mushroom.h"

Skill::Skill(GameObject& associated, Type st, std::weak_ptr<GameObject> player) : Component(associated){
	this->player = player;
	this->st=st;
	active=false;
	coolingdown = false;
	return;
}

void Skill::Update(float dt){
	std::shared_ptr<GameObject> playerpointer = player.lock();
	cdtimer.Update(dt);
	drtimer.Update(dt);
	if(active){
		if(drtimer.Get()>GetDuration()){
			if(st==MUFFLE){
				((Mushroom*)(playerpointer->GetComponent("Mushroom")))->Amplify();
				active=false;
			}
			else if (st == SPEEDBOOST) {
				((Mushroom*)(playerpointer->GetComponent("Mushroom")))->SlowDown();
				active = false;
			}
			else if (st == DASH) {
				active = false;
			}
		}
	}
	if (coolingdown) {
		if (cdtimer.Get() > GetCooldown()) {
			coolingdown = false;
		}
	}
	return;
}

void Skill::Render(){
	return;
}

bool Skill::Is(std::string type){
	if(type=="Skill"){
		return true;
	}
	return false;
}

void Skill::Use(){
	std::shared_ptr<GameObject> playerpointer = player.lock();
	if (coolingdown == false) {
		if (st == MUFFLE) {
			((Mushroom*)(playerpointer->GetComponent("Mushroom")))->Muffle();
		}
		else if (st == SPEEDBOOST) {
			((Mushroom*)(playerpointer->GetComponent("Mushroom")))->SpeedUp();
		}
		else if (st == DASH) {
			if (InputManager::GetInstance().IsKeyDown(SDLK_w) || 
				InputManager::GetInstance().IsKeyDown(SDLK_s) || 
				InputManager::GetInstance().IsKeyDown(SDLK_a) ||
				InputManager::GetInstance().IsKeyDown(SDLK_d)) 
					((Mushroom*)(playerpointer->GetComponent("Mushroom")))->Dash();
			else	
				return;
		}
		cdtimer.Restart();
		drtimer.Restart();
		active = true;
		coolingdown = true;
	}
}

float Skill::GetCooldown(){
	if(st==MUFFLE){
		return 10;
	}
	else if (st == SPEEDBOOST) {
		return 15;
	}
	else if (st == DASH) {
		return 5;
	}
	return 0;
}

float Skill::GetActiveCooldown(){
	if (coolingdown) {
		return GetCooldown() - cdtimer.Get();
	}
	else {
		return 0;
	}
}

Skill::Type Skill::GetType() {
	return st;
}

float Skill::GetDuration(){
	if(st==MUFFLE){
		return 6;
	}
	else if (st == SPEEDBOOST) {
		return 5;
	}
	return 0;
}

std::string Skill::GetSprite(){
	if(st==MUFFLE){
		return "Recursos/img/Icon_chamariz.png";
	}
	else if (st == SPEEDBOOST) {
		return "Recursos/img/Icon_Speed.png";
	}
	else if (st == DASH) {
		return "Recursos/img/Icon_Dash.png";
	}
	return "";
}