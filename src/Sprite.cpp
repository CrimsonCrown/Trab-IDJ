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
	frameCount=1;
	animCount=1;
	frameTime=1;
	currentFrame=0;
	timeElapsed=0;
	repeats=1;
	firstFrame=0;
	lastFrame=0;
	return;
}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, int animCount, float frameTime, float secondsToSelfDestruct, int repeats, int firstFrame, int lastFrame) : Component(associated){
	texture=nullptr;
	angle=0;
	scale.x=1;
	scale.y=1;
	this->frameCount=frameCount;
	this->animCount=animCount;
	this->frameTime=frameTime;
	this->secondsToSelfDestruct=secondsToSelfDestruct;
	this->repeats=repeats;
	this->firstFrame=firstFrame;
	this->lastFrame=lastFrame;
	currentFrame=0;
	timeElapsed=0;
	Open(file);
	SetFrame(firstFrame);
	return;
}

Sprite::~Sprite(){
	return;
}

void Sprite::Open(std::string file){
	texture=Resources::GetImage(file);
	SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);
	associated.box.w=width/frameCount;
	associated.box.h=height/animCount;
	SetClip(0,0,width/frameCount,height/animCount);
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
	for(int i=0;i<repeats;i++){
		SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture,&clipRect,&dstrect,associated.angleDeg,nullptr,SDL_FLIP_NONE);
		dstrect.x+=w;
	}
	return;
}

int Sprite::GetWidth(){
	return (width*scale.x)/frameCount;
}

int Sprite::GetHeight(){
	return (height*scale.y)/animCount;
}

bool Sprite::IsOpen(){
	if(texture!=nullptr){
		return true;
	}
	return false;
}

void Sprite::Update(float dt){
	if(frameCount>1||animCount>1){
		timeElapsed+=dt;
		if(timeElapsed>frameTime){
			timeElapsed-=frameTime;
			currentFrame+=1;
			if(currentFrame>=(frameCount*animCount)||currentFrame>lastFrame){
				currentFrame=firstFrame;
			}
			SetClip(0+((currentFrame%frameCount)*(width/frameCount)),0+((currentFrame/frameCount)*(height/animCount)),width/frameCount,height/animCount);
		}
	}
	if(secondsToSelfDestruct>0){
		selfDestructCount.Update(dt);
		if(selfDestructCount.Get()>secondsToSelfDestruct){
			associated.RequestDelete();
		}
	}
	return;
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

void Sprite::SetFrame(int frame){
	timeElapsed=0;
	currentFrame=frame;
	SetClip(0+((currentFrame%frameCount)*(width/frameCount)),0+((currentFrame/frameCount)*(height/animCount)),width/frameCount,height/animCount);
	return;
}

void Sprite::SetFrameCount(int frameCount, int animCount){
	this->frameCount=frameCount;
	this->animCount=animCount;
	Vec2 oldScale=scale;
	SetScaleX(1,1);
	currentFrame=0;
	SetClip(0+((currentFrame%frameCount)*(width/frameCount)),0+((currentFrame/frameCount)*(height/animCount)),width/frameCount,height/animCount);
	associated.box.w=width/frameCount;
	associated.box.h=height/animCount;
	SetScaleX(oldScale.x,oldScale.y);
	return;
}

void Sprite::SetFrameTime(float frameTime){
	this->frameTime=frameTime;
	return;
}

void Sprite::SetRepeats(int repeats){
	this->repeats=repeats;
	return;
}

void Sprite::SetAnim(int firstFrame, int lastFrame, float frameTime){
	this->firstFrame=firstFrame;
	this->lastFrame=lastFrame;
	this->frameTime=frameTime;
	SetFrame(firstFrame);
	return;
}