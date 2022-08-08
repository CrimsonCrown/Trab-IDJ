#include "Alien.h"
#include "Game.h"

Alien::Alien(GameObject& associated, int nMinions) : Component(associated){
	Sprite* newspr=new Sprite((associated),"Recursos/img/alien.png");
	associated.AddComponent(newspr);
	hp=30;
	return;
}

Alien::~Alien(){
	minionArray.clear();
}

void Alien::Start(){
	for(float arc=0;arc<=PI*2;arc+=PI/2){
		GameObject* minion1=new GameObject();
		Minion* newminion=new Minion((*minion1),Game::GetInstance().GetState().GetObjectPtr(&associated),arc);
		minion1->AddComponent(newminion);
		std::weak_ptr<GameObject> minionptr=Game::GetInstance().GetState().AddObject(minion1);
		minionArray.push_back(minionptr);
	}
	//std::cout << "minions:" << minionArray.size() << "\n";
	return;
}

void Alien::Update(float dt){
	if(InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT)){
		float x=(float)InputManager::GetInstance().GetMouseX()+Camera::pos.x;
		float y=(float)InputManager::GetInstance().GetMouseY()+Camera::pos.y;
		Action newAction(Action::SHOOT,x,y);
		taskQueue.push(newAction);
	}
	if(InputManager::GetInstance().IsMouseDown(SDL_BUTTON_RIGHT)){
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