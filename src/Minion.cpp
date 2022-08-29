#include "Minion.h"
#include "Game.h"
#include "Collider.h"

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated){
	Sprite* newspr=new Sprite((associated),"Recursos/img/minion.png");
	associated.AddComponent(newspr);
	Collider* newcol=new Collider((associated));
	associated.AddComponent(newcol);
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
	Vec2 centerMinion=associated.box.Center();
	Vec2 centerAlien=centerpointer->box.Center();
	Vec2 diff=centerMinion.Sub(centerAlien);
	//2pi=360
	//angle=x
	//(angle*360)/2pi=x
	float angle=((diff.Incline()*360)/(2*PI))+90;
	associated.angleDeg=angle;
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

void Minion::Shoot(Vec2 target){
	Vec2 centerMinion=associated.box.Center();
	Vec2 diff=target.Sub(centerMinion);
	float angle=diff.Incline();
	//cria bullet
	GameObject* bullet=new GameObject();
	Bullet* bulletCpt=new Bullet((*bullet),angle,100,10,3000,"Recursos/img/minionbullet2.png", 3, 0.3,true);
	bullet->AddComponent(bulletCpt);
	bullet->box.x=associated.box.Center().x-(bullet->box.w/2);
	bullet->box.y=associated.box.Center().y-(bullet->box.h/2);
	//2pi=360
	//angle=x
	//(angle*360)/2pi=x
	float angledg=((angle*360)/(2*PI));
	bullet->angleDeg=angledg;
	Game::GetInstance().GetState().AddObject(bullet);
	return;
}