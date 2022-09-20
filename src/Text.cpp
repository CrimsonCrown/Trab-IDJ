#include "Text.h"
#include "Resources.h"
#include "Camera.h"
#include "Game.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float period) : Component(associated){
	this->fontFile=fontFile;
	this->fontSize=fontSize;
	this->style=style;
	this->text=text;
	this->color=color;
	this->period=period;
	renderflag=true;
	texture=nullptr;
	font=Resources::GetFont(fontFile, fontSize);
	RemakeTexture();
	return;
}

Text::~Text(){
	if(texture!=nullptr){
		SDL_DestroyTexture(texture);
	}
	return;
}

void Text::Update(float dt){
	if(period>0){
		timer.Update(dt);
		if(timer.Get()>period){
			timer.Restart();
			renderflag=!renderflag;
		}
	}
	return;
}

void Text::Render(){
	if(renderflag==false){
		return;
	}
	Rect box;
	box=associated.box;
	SDL_Rect cliprect;
	SDL_Rect dstrect;
	cliprect.x=0;
	cliprect.y=0;
	cliprect.w=box.w;
	cliprect.h=box.h;
	dstrect.x=box.x-Camera::pos.x;
	dstrect.y=box.y-Camera::pos.y;
	dstrect.w=box.w;
	dstrect.h=box.h;
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture,&cliprect,&dstrect,associated.angleDeg,nullptr,SDL_FLIP_NONE);
	return;
}

bool Text::Is(std::string type){
	if(type=="Text"){
		return true;
	}
	return false;
}

void Text::SetText(std::string text){
	this->text=text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color){
	this->color=color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style){
	this->style=style;
	RemakeTexture();
}

void Text::SetFontFile(std::string fontFile){
	this->fontFile=fontFile;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize){
	this->fontSize=fontSize;
	RemakeTexture();
}

void Text::RemakeTexture(){
	SDL_Surface* rendered;
	int w,h;
	if(texture!=nullptr){
		SDL_DestroyTexture(texture);
	}
	if(style==SOLID){
		rendered=TTF_RenderText_Solid(font, text.c_str(), color);
	}
	else if(style==SHADED){
		rendered=TTF_RenderText_Shaded(font, text.c_str(), color, {0,0,0,255});
	}
	else if(style==BLENDED){
		rendered=TTF_RenderText_Blended(font, text.c_str(), color);
	}
	texture=SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), rendered);
	SDL_FreeSurface(rendered);
	SDL_QueryTexture(texture,nullptr,nullptr,&w,&h);
	associated.box.w=w;
	associated.box.h=h;
	return;
}