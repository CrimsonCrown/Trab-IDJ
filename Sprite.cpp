#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(){
	texture=nullptr;
	return;
}

Sprite::Sprite(const char* file){
	texture=nullptr;
	Open(file);
	return;
}

Sprite::~Sprite(){
	if(texture!=nullptr){
		SDL_DestroyTexture(texture);
	}
	return;
}

void Sprite::Open(const char* file){
	if(texture!=nullptr){
		SDL_DestroyTexture(texture);
	}
	texture=IMG_LoadTexture(Game::GetInstance().GetRenderer(),file);
	if(texture==nullptr){
		std::cout << SDL_GetError();
	}
	SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);
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

void Sprite::Render(int x, int y){
	SDL_Rect dstrect;
	dstrect.x=x;
	dstrect.y=y;
	dstrect.w=width;
	dstrect.h=height;
	SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstrect);
	return;
}

int Sprite::GetWidth(){
	return width;
}

int Sprite::GetHeight(){
	return height;
}

bool Sprite::IsOpen(){
	if(texture!=nullptr){
		return true;
	}
	return false;
}