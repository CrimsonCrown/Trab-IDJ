#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(){
	isDead=false;
	return;
}

GameObject::~GameObject(){
	std::vector<Component*>::iterator it;
	for(it=components.begin(); it!=components.end(); it++){
		delete *it;
	}
	return;
}

void GameObject::Update(float dt){
	std::vector<Component*>::iterator it;
	for(it=components.begin(); it!=components.end(); it++){
		(*it)->Update(dt);
	}
	return;
}

void GameObject::Render(){
	std::vector<Component*>::iterator it;
	for(it=components.begin(); it!=components.end(); it++){
		(*it)->Render();
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
	components.push_back(cpt);
	return;
}

void GameObject::RemoveComponent(Component* cpt){
	std::vector<Component*>::iterator it;
	for(it=components.begin(); it!=components.end(); it++){
		if(*it==cpt){
			components.erase(it);
		}
	}
	return;
}

Component* GameObject::GetComponent(std::string type){
	std::vector<Component*>::iterator it;
	for(it=components.begin(); it!=components.end(); it++){
		if((*it)->Is(type)){
			return *it;
		}
	}
	return nullptr;
}