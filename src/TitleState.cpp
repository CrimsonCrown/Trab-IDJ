#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "TitleState.h"
#include "StageState.h"
#include "Game.h"

TitleState::TitleState(){
	started=false;
	quitRequested=false;
	popRequested=false;
	//background
	GameObject* bg=new GameObject();
	Sprite* newspr=new Sprite((*bg),"Recursos/img/title.jpg");
	CameraFollower* newflwr=new CameraFollower(*bg);
	bg->AddComponent(newspr);
	bg->AddComponent(newflwr);
	AddObject(bg);
	return;
}

TitleState::~TitleState(){
	objectArray.clear();
}

void TitleState::LoadAssets(){
	/*tileSet = new TileSet(64,64,"Recursos/img/tileset.png");
	GameObject* bg=new GameObject();
	Sprite* newspr=new Sprite((*bg),"Recursos/img/ocean.jpg");
	CameraFollower* newflwr=new CameraFollower(*bg);
	bg->AddComponent(newspr);
	bg->AddComponent(newflwr);
	objectArray.emplace_back(bg);
	GameObject* map=new GameObject();
	TileMap* mapping=new TileMap((*map),"Recursos/map/tileMap.txt", tileSet);
	map->AddComponent(mapping);
	objectArray.emplace_back(map);
	music.Open("Recursos/audio/stageState.ogg");*/
	return;
}

void TitleState::Update(float dt){
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested=true;
	}
	if(InputManager::GetInstance().QuitRequested()){
		quitRequested=true;
	}
	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
		Game& game=Game::GetInstance();
		game.Push(new StageState());
	}
	UpdateArray(dt);
	return;
}

void TitleState::Render(){
	RenderArray();
	return;
}

void TitleState::Start(){
	LoadAssets();
	StartArray();
	started=true;
	return;
}

void TitleState::Pause(){
	return;
}

void TitleState::Resume(){
	return;
}
