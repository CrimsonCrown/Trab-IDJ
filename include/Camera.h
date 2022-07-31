#ifndef CAMERA_INCLUDE
#define CAMERA_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Vec2.h"
#include "GameObject.h"
#include "InputManager.h"

class Camera{
public:
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);
	static Vec2 pos;
	static Vec2 speed;
private:
	static GameObject* focus;
};

#endif