#ifndef NOISE_INCLUDE
#define NOISE_INCLUDE

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

class Noise : public Component{
public:
	Noise(GameObject& associated, Vec2 origin, float radius);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	Vec2 GetOrigin();
	float GetRadius();
	const float duration = 0.4;
private:
	float dtacc;
	Vec2 origin;
	float radius;
};

#endif