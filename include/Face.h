#ifndef FACE_INCLUDE
#define FACE_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"

class Face : public Component{
public:
	Face(GameObject& associated);
	void Damage(int damage);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
	int hitpoints;
};

#endif