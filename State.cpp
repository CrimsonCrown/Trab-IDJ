#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"

State::State(){
	quitRequested=false;
	LoadAssets();
	return;
}

bool State::QuitRequested(){
	return quitRequested;
}

void State::LoadAssets(){
	bg.Open("Recursos/img/ocean.jpg");
	return;
}

void State::Update(float dt){
	//TODO: clisoes, entidades
	//checa quit
	quitRequested=SDL_QuitRequested();
	return;
}

void State::Render(){
	bg.Render(0,0);
	return;
}
