#include "Minion.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated){
	Sprite* newspr=new Sprite((associated),"Recursos/img/minion.png");
	associated.AddComponent(newspr);
	arc=arcOffsetDeg;
	this->alienCenter=alienCenter;
	SetNewPos();
	return;
}

void Minion::SetNewPos(){
	//calcula box
	std::shared_ptr<GameObject> centerpointer=alienCenter.lock();
	Vec2 newpos;
	Vec2 distToCenter(100,0);
	Vec2 centerOffset(associated.box.w/2,associated.box.h/2);
	Vec2 centerPos=centerpointer->box.Center();
	newpos=newpos.Add(distToCenter).Rotate(arc).Sub(centerOffset).Add(centerPos);
	associated.box.x=newpos.x;
	associated.box.y=newpos.y;
	return;
}

void Minion::Update(float dt){
	std::shared_ptr<GameObject> centerpointer=alienCenter.lock();
	if(centerpointer==nullptr){
		associated.RequestDelete();
		return;
	}
	else{
		arc+=(ANGSPEED*dt);
		if(arc>2*PI){
			arc-=2*PI;
		}
		SetNewPos();
	}
	return;
}

void Minion::Render(){
	return;
}

bool Minion::Is(std::string type){
	if(type=="Minion"){
		return true;
	}
	return false;
}