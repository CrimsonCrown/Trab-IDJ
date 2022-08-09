#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(){
	started=false;
	isDead=false;
	angleDeg=0;
	return;
}

GameObject::~GameObject(){
	components.clear();
}

void GameObject::Update(float dt){
	long unsigned int index;
	for(index=0;index<components.size();index++){
		components[index]->Update(dt);
	}
	return;
}

void GameObject::Render(){
	long unsigned int index;
	for(index=0;index<components.size();index++){
		components[index]->Render();
	}
	return;
}

bool GameObject::IsDead(){
	return isDead;
}

void GameObject::RequestDelete(){
	isDead=true;
	return;
}

void GameObject::AddComponent(Component* cpt){
	if(started){
		cpt->Start();
	}
	components.emplace_back(cpt);
	return;
}

void GameObject::RemoveComponent(Component* cpt){
	long unsigned int index;
	for(index=0;index<components.size();index++){
		if(components[index].get()==cpt){
			components.erase(components.begin()+index);
		}
	}
	return;
}

Component* GameObject::GetComponent(std::string type){
	long unsigned int index;
	for(index=0;index<components.size();index++){
		if(components[index]->Is(type)){
			return components[index].get();
		}
	}
	return nullptr;
}

void GameObject::Start(){
	long unsigned int index;
	for(index=0;index<components.size();index++){
		components[index]->Start();
	}
	started=true;
	return;
}