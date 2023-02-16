#include "HearingView.h"
#include "Game.h"
#include "Collider.h"
#include "AIModule.h"

HearingView::HearingView(GameObject& associated, std::weak_ptr<GameObject> earCenter) : Component(associated){
	std::string imagefile;
	if (earCenter.lock()->GetComponent("Enemy")!=nullptr) {
		imagefile = "Recursos/img/Som_cervo.png";
	}
	else {
		imagefile = "Recursos/img/Som_rato.png";
	}
	Sprite* newspr=new Sprite((associated),imagefile,3,1,1,0,1,0,0);
	newspr->SetScaleX(64/associated.box.w, 64/associated.box.h);
	associated.AddComponent(newspr);
	this->earCenter=earCenter;
	SetNewPos();
	return;
}

void HearingView::SetNewPos(){
	//calcula box
	std::shared_ptr<GameObject> centerpointer=earCenter.lock();
	Vec2 newpos;
	Vec2 centerOffset(associated.box.w/2,associated.box.h/2);
	Vec2 centerPos=centerpointer->box.Center();
	newpos=centerPos.Sub(centerOffset);
	associated.box.x=newpos.x;
	associated.box.y=newpos.y;
	return;
}

void HearingView::Update(float dt){
	durTimer.Update(dt);
	std::shared_ptr<GameObject> centerpointer=earCenter.lock();
	if(centerpointer==nullptr){
		associated.RequestDelete();
		return;
	}
	else{
		SetNewPos();
	}
	if (playing) {
		if (durTimer.Get() >= 2) {
			playing = false;
			((Sprite*)associated.GetComponent("Sprite"))->SetAnim(0, 0, 1);
		}
	}
	return;
}

void HearingView::Render(){
	return;
}

bool HearingView::Is(std::string type){
	if(type=="HearingView"){
		return true;
	}
	return false;
}

void HearingView::Play() {
	if (!playing) {
		((Sprite*)associated.GetComponent("Sprite"))->SetAnim(1, 2, 1.0/8.0);
	}
	playing = true;
	durTimer.Restart();
}