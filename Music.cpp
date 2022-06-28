#include "Music.h"

Music::Music(){
	music=nullptr;
	return;
}

Music::Music(const char* file){
	music=nullptr;
	Open(file);
	return;
}

void Music::Play(int times){
	if(music!=nullptr){
		Mix_PlayMusic(music,times);
	}
	else{
		std::cout << "no music loaded\n";
	}
	return;
}

void Music::Stop(int msToStop){
	Mix_FadeOutMusic(msToStop);
	return;
}

void Music::Open(const char* file){
	if(music!=nullptr){
		Mix_FreeMusic(music);
	}
	music=Mix_LoadMUS(file);
	if(music==nullptr){
		std::cout << SDL_GetError();
	}
	return;
}

bool Music::IsOpen(){
	if(music!=nullptr){
		return true;
	}
	return false;
}

Music::~Music(){
	Stop();
	Mix_FreeMusic(music);
	return;
}