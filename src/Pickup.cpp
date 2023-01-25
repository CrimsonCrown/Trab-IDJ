#include "Pickup.h"
#include "Collider.h"


Pickup::Pickup(GameObject& associated, std::string sprite, TileCoords position, Type pt, float tileSize) : Component(associated){
	Sprite* newspr=new Sprite((associated),sprite);
	associated.AddComponent(newspr);
	//newspr->SetScaleX((tileSize/associated.box.w), (tileSize / associated.box.h));
	Collider* newcol=new Collider(associated);
	associated.AddComponent(newcol);
	this->pt=pt;
	newspr->SetScaleX((tileSize/associated.box.w)*0.5, (tileSize / associated.box.h)*0.5);
	associated.box.x+=position.Center(tileSize).x-associated.box.Center().x;
	associated.box.y+=position.Center(tileSize).y-associated.box.Center().y;
	return;
}

void Pickup::Update(float dt){
	return;
}

void Pickup::Render(){
	return;
}

bool Pickup::Is(std::string type){
	if(type=="Pickup"){
		return true;
	}
	return false;
}

Pickup::Type Pickup::GetType(){
	return pt;
}

void Pickup::NotifyCollision(GameObject& other){
	if(other.GetComponent("Mushroom")!=nullptr&&pt==HEALTH){
		associated.RequestDelete();
	}
	if(other.GetComponent("PenguinBody")!=nullptr){
		associated.RequestDelete();
	}
	return;
}