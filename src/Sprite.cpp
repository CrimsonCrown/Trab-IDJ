#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated){
	texture=nullptr;
	angle=0;
	scale.x=1;
	scale.y=1;
	return;
}

Sprite::Sprite(GameObject& associated, std::string file) : Component(associated){
	texture=nullptr;
	angle=0;
	scale.x=1;
	scale.y=1;
	Open(file);
	return;
}

Sprite::~Sprite(){
	return;
}

void Sprite::Open(std::string file){
	texture=Resources::GetImage(file);
	SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);
	associated.box.w=width;
	associated.box.h=height;
	SetClip(0,0,width,height);
	return;
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect.x=x;
	clipRect.y=y;
	clipRect.w=w;
	clipRect.h=h;
	return;
}

void Sprite::Render(){
	Rect box;
	box=associated.box;
	Render(box.x, box.y, box.w, box.h);
	return;
}

void Sprite::Render(int x, int y, int w, int h){
	SDL_Rect dstrect;
	dstrect.x=x-Camera::pos.x;
	dstrect.y=y-Camera::pos.y;
	dstrect.w=w;
	dstrect.h=h;
	//SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstrect);
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstrect,associated.angleDeg,nullptr,SDL_FLIP_NONE);
	return;
}

int Sprite::GetWidth(){
	return width*scale.x;
}

int Sprite::GetHeight(){
	return height*scale.y;
}

bool Sprite::IsOpen(){
	if(texture!=nullptr){
		return true;
	}
	return false;
}

bool Sprite::Is(std::string type){
	if(type=="Sprite"){
		return true;
	}
	return false;
}

void Sprite::SetScaleX(float scaleX, float scaleY){
	Vec2 oldCenter=associated.box.Center();
	if(scaleX!=0){
		float xmult=scaleX/scale.x;
		scale.x=scaleX;
		associated.box.w=associated.box.w*xmult;
	}
	if(scaleY!=0){
		float ymult=scaleY/scale.y;
		scale.y=scaleY;
		associated.box.h=associated.box.h*ymult;
	}
	Vec2 newCenter=associated.box.Center();
	Vec2 diff=oldCenter.Sub(newCenter);
	associated.box=associated.box.Add(diff);
	return;
}

Vec2 Sprite::GetScale(){
	return scale;
}