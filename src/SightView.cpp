#include "SightView.h"
#include "Game.h"
#include "Collider.h"
#include "AIModule.h"

#define PI 3.1415926

SightView::SightView(GameObject& associated, std::weak_ptr<GameObject> eyeCenter, float arcSize, float range) : Component(associated){
	std::string imagefile;
	if (arcSize - (PI / 3.0) * 2.0 < 0.1 && arcSize - (PI / 3.0) * 2.0 > -0.1) {
		imagefile = "Recursos/img/120arc.png";
	}
	else {
		std::cout << arcSize << "\n";
		imagefile = "Recursos/img/90arc.png";
	}
	Sprite* newspr=new Sprite((associated),imagefile);
	float scalebalance = (range / associated.box.w);
	newspr->SetScaleX(scalebalance, scalebalance);
	associated.AddComponent(newspr);
	this->eyeCenter=eyeCenter;
	SetNewPos();
	return;
}

void SightView::SetNewPos(){
	//calcula box
	std::shared_ptr<GameObject> centerpointer=eyeCenter.lock();
	Vec2 newpos;
	Vec2 distToCenter(associated.box.w / 2,0);
	Vec2 centerOffset(associated.box.w/2,associated.box.h/2);
	Vec2 centerPos=centerpointer->box.Center();
	arc = ((AIModule*)(centerpointer->GetComponent("AIModule")))->FacingDirection();
	newpos=newpos.Add(distToCenter).Rotate(arc).Sub(centerOffset).Add(centerPos);
	associated.box.x=newpos.x;
	associated.box.y=newpos.y;
	//2pi=360
	//angle=x
	//(angle*360)/2pi=x
	float angle=((arc*360)/(2*PI));
	associated.angleDeg=angle;
	return;
}

void SightView::Update(float dt){
	std::shared_ptr<GameObject> centerpointer=eyeCenter.lock();
	if(centerpointer==nullptr){
		associated.RequestDelete();
		return;
	}
	else{
		SetNewPos();
	}
	return;
}

void SightView::Render(){
	return;
}

bool SightView::Is(std::string type){
	if(type=="SightView"){
		return true;
	}
	return false;
}