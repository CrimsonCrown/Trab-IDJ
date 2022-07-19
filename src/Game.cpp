#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Game.h"

Game* Game::instance;

Game& Game::GetInstance(){
	if(Game::instance!=nullptr){
		return *Game::instance;
	}
	Game::instance=new Game("Arthur_Da_Silveira_Couto_160002575",1024,600);
	return *Game::instance;
}

Game::Game(const char* title, int width, int height){
	if(Game::instance!=nullptr){
		return;
	}
	srand(time(NULL));
	Game::instance = this;
	//inits
	int error=SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);
	if(error!=0){
		std::cout << SDL_GetError();
	}
	error=IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF);
	if(error!=(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF)){
		std::cout << SDL_GetError();
		std::cout << "IMG_Init fail\n";
	}
	error=Mix_Init(MIX_INIT_FLAC|MIX_INIT_OGG|MIX_INIT_MP3|MIX_INIT_MOD);
	if(error!=(MIX_INIT_FLAC|MIX_INIT_OGG|MIX_INIT_MP3|MIX_INIT_MOD)){
		std::cout << SDL_GetError();
		std::cout << "Mix_Init fail\n";
	}
	error=Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	if(error!=0){
		std::cout << SDL_GetError();
	}
	error=Mix_AllocateChannels(32);
	if(error!=0){
		std::cout << SDL_GetError();
	}
	//janela
	window=SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(window==nullptr){
		std::cout << SDL_GetError();
	}
	//renderer
	renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer==nullptr){
		std::cout << SDL_GetError();
	}
	//state
	state=new State;
}

Game::~Game(){
	//std::cout << "Begin Delete State\n";
	delete state;
	//std::cout << "Deleted state instance\n";
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	//std::cout << "Destroyed game instance\n";
}

State& Game::GetState(){
	return *state;
}

SDL_Renderer* Game::GetRenderer(){
	return renderer;
}

void Game::Run(){
	while(state->QuitRequested()==false){
		//std::cout << "in game debug\n";
		state->Update(0);
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
	return;
}