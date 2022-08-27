#include "Bullet.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime) : Component(associated){
	Sprite* newspr=new Sprite((associated),sprite, frameCount, frameTime);
	associated.AddComponent(newspr);
	this->speed.x=speed;
	this->speed=this->speed.Rotate(angle);
	this->damage=damage;
	distanceLeft=maxDistance;
	return;
}

void Bullet::Update(float dt){
	Vec2 distToMove=speed.Mul(dt);
	associated.box=associated.box.Add(distToMove);
	float distmoved=distToMove.Magnitude();
	distanceLeft-=distmoved;
	if(distanceLeft<=0){
		associated.RequestDelete();
	}
	return;
}

void Bullet::Render(){
	return;
}

bool Bullet::Is(std::string type){
	if(type=="Bullet"){
		return true;
	}
	return false;
}

int Bullet::GetDamage(){
	return damage;
}