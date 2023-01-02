#ifndef GAMEOBJECT_INCLUDE
#define GAMEOBJECT_INCLUDE


#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Rect.h"

class Component;

class GameObject{
public:
	GameObject();
	//GameObject(int renderp,int updatep); //para definir prioridades
	~GameObject();
	void Update(float dt);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	Component* GetComponent(std::string type);
	Rect box;
	void Start();
	bool started;
	double angleDeg;
	void NotifyCollision(GameObject& other);
private:
	//int renderPriority;//bigger means render later
	//int updatePriority;//bigger means update later
	std::vector<std::unique_ptr<Component>> components;
	bool isDead;
};

#endif