#ifndef VEC2_INCLUDE
#define VEC2_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <cmath>

class Vec2{
public:
	Vec2();
	Vec2(float x, float y);
	Vec2 Add(Vec2 vector);
	Vec2 Sub(Vec2 vector);
	Vec2 Mul(float value) const;
	float Magnitude();
	Vec2 Normal();
	float DistTo(Vec2 vector);
	float Incline();
	float Incline(Vec2 vector);
	Vec2 Rotate(float angle);
	float x;
	float y;
private:
};

#endif