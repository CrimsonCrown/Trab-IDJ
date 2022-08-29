#include "Alien.h"
#include "Game.h"
#include "Collider.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated){
	Sprite* newspr=new Sprite((associated),"Recursos/img/alien.png");
	associated.AddComponent(newspr);
	Collider* newcol=new Collider((associated));
	associated.AddComponent(newcol);
	hp=30;
	return;
}

Alien::~Alien(){
	minionArray.clear();
}

void Alien::Start(){
	for(float arc=0;arc<=PI*2;arc+=PI/2){
		float scale=((std::rand())/(RAND_MAX/0.5))+1;
		GameObject* minion1=new GameObject();
		Minion* newminion=new Minion((*minion1),Game::GetInstance().GetState().GetObjectPtr(&associated),arc);
		minion1->AddComponent(newminion);
		((Sprite*)minion1->GetComponent("Sprite"))->SetScaleX(scale,scale);
		std::weak_ptr<GameObject> minionptr=Game::GetInstance().GetState().AddObject(minion1);
		minionArray.push_back(minionptr);
	}
	//std::cout << "minions:" << minionArray.size() << "\n";
	return;
}

void Alien::Update(float dt){
	if(InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)){
		float x=(float)InputManager::GetInstance().GetMouseX()+Camera::pos.x;
		float y=(float)InputManager::GetInstance().GetMouseY()+Camera::pos.y;
		Action newAction(Action::SHOOT,x,y);
		taskQueue.push(newAction);
	}
	if(InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT)){
		float x=(float)InputManager::GetInstance().GetMouseX()+Camera::pos.x;
		float y=(float)InputManager::GetInstance().GetMouseY()+Camera::pos.y;
		Action newAction(Action::MOVE,x,y);
		taskQueue.push(newAction);
	}
	if(taskQueue.size()>0){
		Action todo=taskQueue.front();
		if(todo.type==Action::MOVE){
			Vec2 boxPos=associated.box.Center();
			float distToMove=300*dt;
			if(todo.pos.DistTo(boxPos)<=distToMove){
				associated.box.x=todo.pos.x-(associated.box.w/2);
				associated.box.y=todo.pos.y-(associated.box.h/2);
				taskQueue.pop();
			}
			else{
				speed=todo.pos.Sub(boxPos).Normal().Mul(distToMove);
				associated.box=associated.box.Add(speed);
			}
		}
		else if(todo.type==Action::SHOOT){
			int index;
			long unsigned int i;
			float distFromMinion;
			index=0;
			distFromMinion=1000000000;
			Rect targetRect(todo.pos.x,todo.pos.y,0,0);
			for(i=0;i<minionArray.size();i++){
				std::shared_ptr<GameObject> minionTest=minionArray[i].lock();
				if(minionTest->box.CenterDist(targetRect)<distFromMinion){
					distFromMinion=minionTest->box.CenterDist(targetRect);
					index=i;
				}
			}
			std::shared_ptr<GameObject> minionShooter=minionArray[index].lock();
			Vec2 target(todo.pos.x,todo.pos.y);
			if(minionShooter!=nullptr){
				((Minion*)(minionShooter->GetComponent("Minion")))->Shoot(target);
			}
			taskQueue.pop();
		}
	}
	associated.angleDeg-=(30*dt);
	if(associated.angleDeg<=0){
		associated.angleDeg+=360;
	}
	if(hp==0){
		associated.RequestDelete();
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
	}
	return;
}