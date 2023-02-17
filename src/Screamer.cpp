#include "Screamer.h"
#include "Noise.h"
#include "Game.h"

Screamer::Screamer(GameObject& associated, float noiseRadius) : Component(associated){
	this->seeing=false;
    this->noiseRadius = noiseRadius;
	return;
}

void Screamer::Update(float dt){
	
}

void Screamer::Render(){
	return;
}

bool Screamer::Is(std::string type){
	if(type=="Screamer"){
		return true;
	}
	return false;
}

void Screamer::CreateNoise(Vec2 position) {
    GameObject* noise=new GameObject();
    Noise* newnoise=new Noise((*noise), position, noiseRadius);
    noise->AddComponent(newnoise);
    Game::GetInstance().GetCurrentState().AddObject(noise);
}