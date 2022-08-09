#include "Vec2.h"

Vec2::Vec2(){
	x=0;
	y=0;
	return;
}

Vec2::Vec2(float x, float y){
	this->x=x;
	this->y=y;
	return;
}

Vec2 Vec2::Add(Vec2 vector){
	Vec2 result;
	result.x=x+vector.x;
	result.y=y+vector.y;
	return result;
}

Vec2 Vec2::Sub(Vec2 vector){
	Vec2 result;
	result.x=x-vector.x;
	result.y=y-vector.y;
	return result;
}

Vec2 Vec2::Mul(float value){
	Vec2 result;
	result.x=x*value;
	result.y=y*value;
	return result;
}

float Vec2::Magnitude(){
	return sqrt(pow(x,2)+pow(y,2));
}

Vec2 Vec2::Normal(){
	float mag=Magnitude();
	Vec2 result;
	result.x=x/mag;
	result.y=y/mag;
	return result;
}

float Vec2::DistTo(Vec2 vector){
	Vec2 dif=Sub(vector);
	return dif.Magnitude();
}

float Vec2::Incline(){
	return atan2(y,x);
}

float Vec2::Incline(Vec2 vector){
	Vec2 dif=Sub(vector);
	return dif.Incline();
}

Vec2 Vec2::Rotate(float angle){
	float xn,yn,s,c;
	s=sin(angle);
	c=cos(angle);
	xn=(x*c)-(y*s);
	yn=(y*c)+(x*s);
	return Vec2(xn,yn);
}