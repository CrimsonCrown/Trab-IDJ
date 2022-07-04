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
	~GameObject();
	void Update(float dt);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	Component* GetComponent(std::string type);
	Rect box;
private:
	std::vector<std::unique_ptr<Component>> components;
	bool isDead;
};

#endif