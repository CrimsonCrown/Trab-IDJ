#ifndef RECT_INCLUDE
#define RECT_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

#include <Vec2.h>

class Rect{
public:
	Rect();
	Rect(float x, float y, float w, float h);
	Rect Add(Vec2 vector);
	Vec2 Center();
	float CenterDist(Rect rectangle);
	bool Contains(Vec2 point);
	float x;
	float y;
	float w;
	float h;
private:
};

#endif