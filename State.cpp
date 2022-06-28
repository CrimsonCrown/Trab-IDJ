#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"

State::State(){
	quitRequested=false;
	return;
}

bool State::QuitRequested(){
	return quitRequested;
}

void State::LoadAssets(){
	//TODO: Load Anything
	return;
}

void State::Update(float dt){
	//TODO: clisoes, entidades
	//checa quit
	quitRequested=SDL_QuitRequested();
	return;
}

void State::Render(){
	bg.Render();
	return;
}
