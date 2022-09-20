#include "Alien.h"
#include "Game.h"
#include "Collider.h"
#include "PenguinBody.h"

int Alien::alienCount=0;

Alien::Alien(GameObject& associated, int nMinions, float alienDelay) : Component(associated){
	Sprite* newspr=new Sprite((associated),"Recursos/img/alien.png");
	associated.AddComponent(newspr);
	Collider* newcol=new Collider((associated));
	associated.AddComponent(newcol);
	hp=30;
	alienCount++;
	state=RESTING;
	this->alienDelay=alienDelay;
	return;
}

Alien::~Alien(){
	minionArray.clear();
	alienCount--;
}

void Alien::Start(){
	for(float arc=0;arc<=PI*2;arc+=PI/2){
		float scale=((std::rand())/(RAND_MAX/0.5))+1;
		GameObject* minion1=new GameObject();
		Minion* newminion=new Minion((*minion1),Game::GetInstance().GetCurrentState().GetObjectPtr(&associated),arc);
		minion1->AddComponent(newminion);
		((Sprite*)minion1->GetComponent("Sprite"))->SetScaleX(scale,scale);
		std::weak_ptr<GameObject> minionptr=Game::GetInstance().GetCurrentState().AddObject(minion1);
		minionArray.push_back(minionptr);
	}
	//std::cout << "minions:" << minionArray.size() << "\n";
	return;
}

void Alien::Update(float dt){
	associated.angleDeg-=(30*dt);
	if(associated.angleDeg<=0){
		associated.angleDeg+=360;
	}
	if(PenguinBody::player==nullptr){
		return;
	}
	if(state==RESTING){
		if(restTimer.Get()>alienDelay){
			destination=PenguinBody::player->Position();
			state=MOVING;
		}
		else{
			restTimer.Update(dt);
		}
	}
	else{
		if(associated.box.Center().DistTo(destination)==0){
			state=RESTING;
			restTimer.Restart();
			destination=PenguinBody::player->Position();
			int index;
			long unsigned int i;
			float distFromMinion;
			index=0;
			distFromMinion=1000000000;
			for(i=0;i<minionArray.size();i++){
				std::shared_ptr<GameObject> minionTest=minionArray[i].lock();
				if(minionTest->box.Center().DistTo(destination)<distFromMinion){
					distFromMinion=minionTest->box.Center().DistTo(destination);
					index=i;
				}
			}
			std::shared_ptr<GameObject> minionShooter=minionArray[index].lock();
			if(minionShooter!=nullptr){
				((Minion*)(minionShooter->GetComponent("Minion")))->Shoot(destination);
			}
		}
		else{
			Vec2 boxPos=associated.box.Center();
			float distToMove=100*dt;
			if(destination.DistTo(boxPos)<=distToMove){
				associated.box.x=destination.x-(associated.box.w/2);
				associated.box.y=destination.y-(associated.box.h/2);
			}
			else{
				speed=destination.Sub(boxPos).Normal().Mul(distToMove);
				associated.box=associated.box.Add(speed);
			}
		}
	}
	return;
}

void Alien::Render(){
	return;
}

bool Alien::Is(std::string type){
	if(type=="Alien"){
		return true;
	}
	return false;
}

void Alien::NotifyCollision(GameObject& other){
	if((other.GetComponent("Bullet")!=nullptr)&&(((Bullet*)other.GetComponent("Bullet"))->targetsPlayer==false)){
		hp-=10;
		if(hp<=0){
			GameObject* explosion=new GameObject();
			Sprite* newspr=new Sprite((*explosion),"Recursos/img/aliendeath.png", 4, 0.5, 2);
			explosion->AddComponent(newspr);
			Sound* newsnd=new Sound((*explosion),"Recursos/audio/boom.wav");
			newsnd->Play();
			explosion->AddComponent(newsnd);
			explosion->box=explosion->box.Add(associated.box.Center().Sub(explosion->box.Center()));
			Game::GetInstance().GetCurrentState().AddObject(explosion);
			associated.RequestDelete();
		}
	}
	return;
}