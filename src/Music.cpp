#include "Music.h"

Music::Music(){
	music=nullptr;
	return;
}

Music::Music(std::string file){
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

void Music::Open(std::string file){
	music=Resources::GetMusic(file);
	return;
}

bool Music::IsOpen(){
	if(music!=nullptr){
		return true;
	}
	return false;
}

Music::~Music(){
	Stop(0);
	return;
}