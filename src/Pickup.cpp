#include "Pickup.h"
#include "Collider.h"


Pickup::Pickup(GameObject& associated, TileCoords position, Type pt, float tileSize) : Component(associated){
	this->pt = pt;
	Sprite* newspr=new Sprite((associated),GetSprite());
	associated.AddComponent(newspr);
	//newspr->SetScaleX((tileSize/associated.box.w), (tileSize / associated.box.h));
	Collider* newcol=new Collider(associated);
	associated.AddComponent(newcol);
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
	if(other.GetComponent("Mushroom")!=nullptr){
		associated.RequestDelete();
	}
	return;
}

std::string Pickup::GetSprite() {
	if (pt == MUFFLE) {
		return "Recursos/img/Icon_chamariz.png";
	}
	else if (pt == HEALTH) {
		return "Recursos/img/Icon_life.png";
	}
	else if (pt == SPEEDBOOST) {
		return "Recursos/img/Icon_Speed.png";
	}
	else if (pt == DASH) {
		return "Recursos/img/Icon_Dash.png";
	}
	return "";
}