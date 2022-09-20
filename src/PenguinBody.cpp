#include "PenguinBody.h"
#include "Game.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"

#define PI 3.1415926

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated){
	player=this;
	Collider* newcol=new Collider((associated));
	associated.AddComponent(newcol);
	//cria sprite
	Sprite* newspr=new Sprite((associated),"Recursos/img/penguin.png");
	associated.AddComponent(newspr);
	//outros atributos
	linearSpeed=speed.Magnitude();
	angle=0;
	hp=30;
	return;
}

PenguinBody::~PenguinBody(){
	player=nullptr;
	return;
}

void PenguinBody::Start(){
	//cria PenguinCannon
	GameObject* penguinBuddy=new GameObject();
	PenguinCannon* newcannon=new PenguinCannon((*penguinBuddy),Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
	penguinBuddy->AddComponent(newcannon);
	pcannon=Game::GetInstance().GetCurrentState().AddObject(penguinBuddy);
	return;
}

void PenguinBody::Update(float dt){
	float maxspeed=80;
	float minspeed=-80;
	float speedps=25;
	float angleps=PI/3;
	float speeddelta=0;
	float angledelta=0;
	if(InputManager::GetInstance().IsKeyDown(SDLK_w)){
		speeddelta+=speedps*dt;
	}
	if(InputManager::GetInstance().IsKeyDown(SDLK_s)){
		speeddelta-=speedps*dt;
	}
	if(InputManager::GetInstance().IsKeyDown(SDLK_a)){
		angledelta-=angleps*dt;
	}
	if(InputManager::GetInstance().IsKeyDown(SDLK_d)){
		angledelta+=angleps*dt;
	}
	//calcula velocidade e angulo
	linearSpeed+=speeddelta;
	if(linearSpeed>maxspeed){linearSpeed=maxspeed;}
	if(linearSpeed<minspeed){linearSpeed=minspeed;}
	angle+=angledelta;
	if(angle>(2*PI)){angle-=(2*PI);}
	if(angle<0){angle+=(2*PI);}
	//calcula velocidade final
	speed.x=linearSpeed;
	speed.y=0;
	speed=speed.Rotate(angle);
	//aplica no objeto
	associated.box=associated.box.Add(speed.Mul(dt));
	if(associated.box.x<0){
		associated.box.x=0;
	}
	if(associated.box.y<0){
		associated.box.y=0;
	}
	if(associated.box.x>1408){
		associated.box.x=1408;
	}
	if(associated.box.y>1280){
		associated.box.y=1280;
	}
	associated.angleDeg=((angle*360)/(2*PI));
	//morre com 0 hp
	return;
}

void PenguinBody::Render(){
	return;
}

bool PenguinBody::Is(std::string type){
	if(type=="PenguinBody"){
		return true;
	}
	return false;
}

void PenguinBody::NotifyCollision(GameObject& other){
	if((other.GetComponent("Bullet")!=nullptr)&&(((Bullet*)other.GetComponent("Bullet"))->targetsPlayer==true)){
		hp-=10;
		if(hp<=0){
			Camera::Unfollow();
			GameObject* explosion=new GameObject();
			Sprite* newspr=new Sprite((*explosion),"Recursos/img/penguindeath.png", 5, 0.4, 2);
			explosion->AddComponent(newspr);
			Sound* newsnd=new Sound((*explosion),"Recursos/audio/boom.wav");
			newsnd->Play();
			explosion->AddComponent(newsnd);
			explosion->box=explosion->box.Add(associated.box.Center().Sub(explosion->box.Center()));
			Game::GetInstance().GetCurrentState().AddObject(explosion);
			pcannon.lock()->RequestDelete();
			associated.RequestDelete();
		}
	}
	return;
}

Vec2 PenguinBody::Position(){
	return associated.box.Center();
}