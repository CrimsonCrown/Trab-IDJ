#include "Bullet.h"
#include "Collider.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool tp) : Component(associated){
	Sprite* newspr=new Sprite((associated),sprite, frameCount, frameTime);
	associated.AddComponent(newspr);
	Vec2 scale={1,1};
	Vec2 offset={speed/30,0};
	Collider* newcol=new Collider(associated, scale, offset);
	associated.AddComponent(newcol);
	this->speed.x=speed;
	this->speed=this->speed.Rotate(angle);
	this->damage=damage;
	targetsPlayer=tp;
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

void Bullet::NotifyCollision(GameObject& other){
	if(other.GetComponent("Alien")!=nullptr&&targetsPlayer==false){
		associated.RequestDelete();
	}
	if(other.GetComponent("PenguinBody")!=nullptr&&targetsPlayer==true){
		associated.RequestDelete();
	}
	return;
}