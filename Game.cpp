#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Game.h"

Game* Game::instance;

Game& Game::GetInstance(){
	if(Game::instance!=nullptr){
		return *Game::instance;
	}
	Game::instance=new Game("hello",1920,1080);
	return *Game::instance;
}

Game::Game(std::string title, int width, int height){
	if(Game::instance!=nullptr){
		return;
	}
	Game::instance = this;
	int error=SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);
	if(error!=0){
		std::cout << SDL_GetError();
	}
}