#ifndef COMPONENT_INCLUDE
#define COMPONENT_INCLUDE


#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

class GameObject;

class Component{
public:
	Component(GameObject& associated);
	virtual ~Component();
	virtual void Update(float dt)=0;
	virtual void Render()=0;
	virtual bool Is(std::string type)=0;
	virtual void Start(){}
protected:
	GameObject& associated;
};

#endif