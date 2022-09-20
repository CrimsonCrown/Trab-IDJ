#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "EndState.h"
#include "Game.h"
#include "Text.h"
#include "Camera.h"
#include "GameData.h"

EndState::EndState(){
	started=false;
	quitRequested=false;
	popRequested=false;
	if(GameData::playerVictory){
		//background
		GameObject* bg=new GameObject();
		Sprite* newspr=new Sprite((*bg),"Recursos/img/win.jpg");
		CameraFollower* newflwr=new CameraFollower(*bg);
		bg->AddComponent(newspr);
		bg->AddComponent(newflwr);
		AddObject(bg);
		//text
		GameObject* text=new GameObject();
		Text* newtxt=new Text((*text),"Recursos/font/Call me maybe.ttf", 55, Text::TextStyle::SOLID, "Press Space to Try Again, or ESC to Quit", {255,255,255,255}, 1);
		text->AddComponent(newtxt);
		//CameraFollower* newflwr2=new CameraFollower(*text);
		//text->AddComponent(newflwr2);
		text->box.y=500;
		text->box.x=30;
		AddObject(text);
		//music
		backgroundMusic.Open("Recursos/audio/endStateWin.ogg");
		backgroundMusic.Play();
	}
	else{
		//background
		GameObject* bg=new GameObject();
		Sprite* newspr=new Sprite((*bg),"Recursos/img/lose.jpg");
		CameraFollower* newflwr=new CameraFollower(*bg);
		bg->AddComponent(newspr);
		bg->AddComponent(newflwr);
		AddObject(bg);
		//text
		GameObject* text=new GameObject();
		Text* newtxt=new Text((*text),"Recursos/font/Call me maybe.ttf", 55, Text::TextStyle::SOLID, "Press Space to Try Again, or ESC to Quit", {255,255,255,255}, 1);
		text->AddComponent(newtxt);
		//CameraFollower* newflwr2=new CameraFollower(*text);
		//text->AddComponent(newflwr2);
		text->box.y=10;
		text->box.x=30;
		AddObject(text);
		//music
		backgroundMusic.Open("Recursos/audio/endStateLose.ogg");
		backgroundMusic.Play();
	}
	return;
}

EndState::~EndState(){
	objectArray.clear();
}

void EndState::LoadAssets(){
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

void EndState::Update(float dt){
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		quitRequested=true;
	}
	if(InputManager::GetInstance().QuitRequested()){
		quitRequested=true;
	}
	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
		popRequested=true;
	}
	Camera::pos.x=0;
	Camera::pos.y=0;
	UpdateArray(dt);
	return;
}

void EndState::Render(){
	RenderArray();
	return;
}

void EndState::Start(){
	LoadAssets();
	StartArray();
	started=true;
	return;
}

void EndState::Pause(){
	return;
}

void EndState::Resume(){
	return;
}
