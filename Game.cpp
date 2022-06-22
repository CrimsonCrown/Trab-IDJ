#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Game.h"


static Game& Game::GetInstance(){
	if(instance!=nullptr){
		return *instance;
	}
	instance=new Game;
	return *instance;
}

Game::Game(string title, int width, int height){
	if(instance!=nullptr){
		return 0;
	}
	instance = this;
	int error=SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);
	if(error!=0){
		cout << SDL_GetError();
	}
}