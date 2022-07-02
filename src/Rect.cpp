#include "Rect.h"

Rect::Rect(){
	x=0;
	y=0;
	w=0;
	h=0;
	return;
}

Rect::Rect(float x, float y, float w, float h){
	this->x=x;
	this->y=y;
	this->w=w;
	this->h=h;
	return;
}

Rect Rect::Add(Vec2 vector){
	Rect result;
	result.x=x+vector.x;
	result.y=y+vector.y;
	result.w=w;
	result.h=h;
	return result;
}

Vec2 Rect::Center(){
	Vec2 result;
	result.x=(x+w)/2;
	result.y=(y+h)/2;
	return result;
}

float Rect::CenterDist(Rect rectangle){
	Vec2 center1,center2;
	center1=Center();
	center2=rectangle.Center();
	return center1.DistTo(center2);
}

bool Rect::Contains(Vec2 point){
	if((point.x)>(x+w)||(point.x)<x||(point.y)>(y+h)||(point.y)<y){
		return false;
	}
	return true;
}