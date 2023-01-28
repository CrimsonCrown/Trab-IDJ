#include "Skill.h"
#include "Game.h"
#include "Collider.h"
#include "Mushroom.h"

Skill::Skill(GameObject& associated, Type st) : Component(associated){
	this->st=st;
	active=false;
	coolingdown = false;
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
	if(st==MUFFLE){
		//std::cout << "skill muffle was used ";
		if(coolingdown==false){
			//std::cout << "succesfully!";
			Mushroom::player->Muffle();
			cdtimer.Restart();
			drtimer.Restart();
			active=true;
			coolingdown = true;
		}
		else {
			//std::cout << "but it was on cooldown!";
		}
		//std::cout << "\n";
	}
}

float Skill::GetCooldown(){
	if(st==MUFFLE){
		return 10;
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
		return "Recursos/img/Icon_chamariz.png";
	}
	return "";
}