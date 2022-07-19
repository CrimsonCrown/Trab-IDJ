#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file){
	if(Resources::imageTable.find(file)!=Resources::imageTable.end()){
		return Resources::imageTable.at(file);
	}
	else{
		OpenImage(file);
		return Resources::imageTable.at(file);
	}
}

void Resources::ClearImages(){
	for(auto it=Resources::imageTable.begin();it!=Resources::imageTable.end();it++){
		SDL_DestroyTexture(std::get<1>(*it));
	}
	Resources::imageTable.clear();
	return;
}

Mix_Music* Resources::GetMusic(std::string file){
	if(Resources::musicTable.find(file)!=Resources::musicTable.end()){
		return Resources::musicTable.at(file);
	}
	else{
		OpenMusic(file);
		return Resources::musicTable.at(file);
	}
}

void Resources::ClearMusics(){
	for(auto it=Resources::musicTable.begin();it!=Resources::musicTable.end();it++){
		Mix_FreeMusic(std::get<1>(*it));
	}
	Resources::musicTable.clear();
	return;
}

Mix_Chunk* Resources::GetSound(std::string file){
	if(Resources::soundTable.find(file)!=Resources::soundTable.end()){
		return Resources::soundTable.at(file);
	}
	else{
		OpenSound(file);
		return Resources::soundTable.at(file);
	}
}

void Resources::ClearSounds(){
	for(auto it=Resources::soundTable.begin();it!=Resources::soundTable.end();it++){
		Mix_FreeChunk(std::get<1>(*it));
	}
	Resources::musicTable.clear();
	return;
}


void Resources::OpenImage(std::string file){
	SDL_Texture* texture;
	if(Resources::imageTable.find(file)==Resources::imageTable.end()){
		texture=IMG_LoadTexture(Game::GetInstance().GetRenderer(),file.c_str());
		if(texture==nullptr){
			std::cout << SDL_GetError();
		}
		Resources::imageTable.insert({file,texture});
	}
	return;
}

void Resources::OpenMusic(std::string file){
	Mix_Music* music;
	if(Resources::musicTable.find(file)==Resources::musicTable.end()){
		music=Mix_LoadMUS(file.c_str());
		if(music==nullptr){
			std::cout << SDL_GetError();
		}
		Resources::musicTable.insert({file,music});
	}
	return;
}

void Resources::OpenSound(std::string file){
	Mix_Chunk* chunk;
	if(Resources::soundTable.find(file)==Resources::soundTable.end()){
		chunk=Mix_LoadWAV(file.c_str());
		if(chunk==nullptr){
			std::cout << SDL_GetError();
		}
		Resources::soundTable.insert({file,chunk});
	}
	return;
}
