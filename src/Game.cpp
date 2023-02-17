#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include "Game.h"
#include "Resources.h"

Game* Game::instance;

Game& Game::GetInstance(){
	if(Game::instance!=nullptr){
		return *Game::instance;
	}
	Game::instance=new Game("Fungitive",1024,576);
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
	//ttf
	if(TTF_Init()!=0){
		std::cout << "TTF init fail\n";
	}
	//state
	storedState=nullptr;
	//frameStart e dt
	frameStart=SDL_GetTicks();
	dt=0;
}

Game::~Game(){
	//std::cout << "Begin Delete State\n";
	if(storedState!=nullptr){
		delete storedState;
	}
	//std::cout << "Deleted state instance\n";
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
	while(!stateStack.empty()){
		stateStack.pop();
	}
	//std::cout << "Destroyed game instance\n";
}

State& Game::GetCurrentState(){
	return *stateStack.top();
}

SDL_Renderer* Game::GetRenderer(){
	return renderer;
}

void Game::Run(){
	if(storedState==nullptr){
		return;
	}
	//SDL_ShowCursor(SDL_DISABLE);
	stateStack.emplace(storedState);
	storedState=nullptr;
	stateStack.top()->Start();
	while(!stateStack.empty()&&stateStack.top()->QuitRequested()==false){
		//remove estado
		if(stateStack.top()->PopRequested()){
			stateStack.pop();
			if(!stateStack.empty()){
				stateStack.top()->Resume();
			}
		}
		//adiciona estado
		if(storedState!=nullptr){
			stateStack.top()->Pause();
			stateStack.emplace(storedState);
			storedState=nullptr;
			stateStack.top()->Start();
		}
		//opera estado atual
		if(!stateStack.empty()){
			CalculateDeltaTime();
			InputManager::GetInstance().Update();
			stateStack.top()->Update(dt);
			stateStack.top()->Render();
			SDL_RenderPresent(renderer);
			SDL_Delay(33);
		}
	}
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
	return;
}

void Game::CalculateDeltaTime(){
	int newframestart;
	newframestart=SDL_GetTicks();
	dt=(newframestart-frameStart)/1000.0;
	frameStart=newframestart;
	return;
}

float Game::GetDeltaTime(){
	return dt;
}

void Game::Push(State* state){
	storedState=state;
}