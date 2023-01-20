#include "SightRay.h"
#include "Collider.h"
#include "Bush.h"

SightRay::SightRay(GameObject& associated, Vision& eye, Vec2 origin, Vec2 destiny, float girth) : Component(associated), eye(eye){
	Collider* newcol=new Collider(associated);
	associated.AddComponent(newcol);
	Vec2 newcenter=destiny.Sub(origin).Mul(0.5).Add(origin);
	associated.box.w=destiny.Sub(origin).Magnitude();
	associated.box.h=girth;
	associated.angleDeg=(destiny.Sub(origin).Incline()*360)/(2*PI);
	associated.box.x=associated.box.x+(newcenter.x-associated.box.Center().x);
	associated.box.y=associated.box.y+(newcenter.y-associated.box.Center().y);
	todie=false;
	return;
}

void SightRay::Update(float dt){
	if(todie){
		associated.RequestDelete();
	}
	else{
		todie=true;
	}
}

void SightRay::Render(){
	return;
}

bool SightRay::Is(std::string type){
	if(type=="SightRay"){
		return true;
	}
	return false;
}

void SightRay::NotifyCollision(GameObject& other){
	if(other.GetComponent("Wall")!=nullptr){
		eye.Blocked();
	}
	else if(other.GetComponent("Bush")!=nullptr){
		if(((Bush*)(other.GetComponent("Bush")))->Ocupied()){
			eye.Blocked();
		}
	}
	return;
}