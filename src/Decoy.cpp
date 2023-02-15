#include "Decoy.h"
#include "Noise.h"
#include "Game.h"
#include "Mushroom.h"

Decoy::Decoy(GameObject& associated, float tileSize) : Component(associated){
    this->tileSize = tileSize;
    noiseRadius = 5;
    std::string spriteArray[] = {"Recursos/img/Chamariz_1.png", "Recursos/img/Chamariz_2.png", "Recursos/img/Chamariz_3.png", "Recursos/img/Chamariz_4.png"};
    std::string sprite = spriteArray[rand() % 4];
    float lifespan = 10;
	Sprite* newspr=new Sprite((associated), sprite, 1, 1, 1, lifespan);
    newspr->SetScaleX((tileSize/associated.box.w), (tileSize / associated.box.h));
	associated.AddComponent(newspr);
	return;
}

void Decoy::Update(float dt){
    timer.Update(dt);
    if (timer.Get() >= 1.5) {    
        GameObject* noise=new GameObject();
        Noise* newnoise=new Noise((*noise), associated.box.Center(), tileSize*noiseRadius);
        noise->AddComponent(newnoise);
        Game::GetInstance().GetCurrentState().AddObject(noise);
        timer.Restart();
    }
}

void Decoy::Render(){
	return;
}

bool Decoy::Is(std::string type){
	if(type=="Decoy"){
		return true;
	}
	return false;
}