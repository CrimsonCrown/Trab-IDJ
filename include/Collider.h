#ifndef COLLIDER_INCLUDE
#define COLLIDER_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <queue>

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"

class Collider : public Component{
public:
	Collider(GameObject& associated, Vec2 scale={1,1}, Vec2 offset={0,0});
	Rect box;
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void SetScale(Vec2 scale);
	void SetOffset(Vec2 offset);
private:
	Vec2 scale;
	Vec2 offset;
};

#endif