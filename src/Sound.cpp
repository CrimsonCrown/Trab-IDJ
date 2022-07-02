#include "Sound.h"

Sound::Sound(GameObject& associated) : Component(associated){
	chunk=nullptr;
	return;
}

Sound::Sound(GameObject& associated, std::string file) : Sound(associated){
	Open(file);
	return;
}

Sound::~Sound(){
	Stop();
	if(chunk!=nullptr)Mix_FreeChunk(chunk);
	return;
}

void Sound::Play(int times){
	channel=Mix_PlayChannel(-1,chunk,times);
	return;
}

void Sound::Stop(){
	if(chunk!=nullptr){
		Mix_HaltChannel(channel);
	}
	return;
}

void Sound::Open(std::string file){
	if(chunk!=nullptr){
		Mix_FreeChunk(chunk);
	}
	chunk=Mix_LoadWAV(file.c_str());
	if(chunk==nullptr){
		std::cout << SDL_GetError();
	}
	return;
}

bool Sound::IsOpen(){
	if(chunk!=nullptr){
		return true;
	}
	return false;
}

void Sound::Update(float dt){
	return;
}

void Sound::Render(){
	return;
}

bool Sound::Is(std::string type){
	if(type=="Sound"){
		return true;
	}
	return false;
}