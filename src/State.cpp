#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"
#include "Collision.h"
#include "Collider.h"

State::State(){
	started=false;
	quitRequested=false;
	popRequested=false;
	return;
}

State::~State(){
	objectArray.clear();
}

bool State::QuitRequested(){
	return quitRequested;
}

bool State::PopRequested(){
	return popRequested;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
	//constroi shared ptr
	std::shared_ptr<GameObject> newobj(go);
	//coloca no vetor
	objectArray.push_back(newobj);
	//start caso necessario
	if(started){
		newobj->Start();
	}
	//retorna weak ptr
	std::weak_ptr<GameObject> newweak(newobj);
	return newweak;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
	//varre vetor
	long unsigned int index;
	for(index=0;index<objectArray.size();index++){
		if(objectArray[index].get()==go){
			std::weak_ptr<GameObject> newweak(objectArray[index]);
			return newweak;
		}
	}
	std::weak_ptr<GameObject> newweak;
	return newweak;
}

void State::UpdateArray(float dt){
	long unsigned int index;
	for(index=0;index<objectArray.size();index++){
		objectArray[index]->Update(dt);
	}
	return;
}

void State::RenderArray(){
	long unsigned int index;
	for(index=0;index<objectArray.size();index++){
		objectArray[index]->Render();
	}
	return;
}

void State::StartArray(){
	long unsigned int index;
	for(index=0;index<objectArray.size();index++){
		objectArray[index]->Start();
	}
	return;
}