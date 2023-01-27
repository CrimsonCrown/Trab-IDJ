#include "Skill.h"
#include "Game.h"
#include "Collider.h"
#include "Mushroom.h"

Skill::Skill(GameObject& associated, Type st) : Component(associated){
	this->st=st;
	active=false;
	return;
}

void Skill::Update(float dt){
	cdtimer.Update(dt);
	drtimer.Update(dt);
	if(active){
		if(drtimer.Get()>GetDuration()){
			if(st==MUFFLE){
				Mushroom::player->Amplify();
				active=false;
			}
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
	if(st==MUFFLE){
		if(cdtimer.Get()>GetCooldown()){
			Mushroom::player->Muffle();
			cdtimer.Restart();
			drtimer.Restart();
			active=true;
		}
	}
}

float Skill::GetCooldown(){
	if(st==MUFFLE){
		return 60;
	}
	return 0;
}

float Skill::GetActiveCooldown(){
	return GetCooldown()-cdtimer.Get();
}

float Skill::GetDuration(){
	if(st==MUFFLE){
		return 6;
	}
	return 0;
}

std::string Skill::GetSprite(){
	if(st==MUFFLE){
		return "Resources/img/penguinface.png";
	}
	return "";
}