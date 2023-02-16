#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "TitleState.h"
#include "StageState.h"
#include "Game.h"
#include "Text.h"
#include "Camera.h"
#include "MenuButton.h"
#include "TutorialState.h"

TitleState::TitleState(){
	started=false;
	quitRequested=false;
	popRequested=false;
	//background
	GameObject* bg=new GameObject();
	Sprite* newspr=new Sprite((*bg),"Recursos/img/Tela_menu.png");
	newspr->SetScaleX((1024 / bg->box.w), (576 / bg->box.h));
	CameraFollower* newflwr=new CameraFollower(*bg);
	bg->AddComponent(newspr);
	bg->AddComponent(newflwr);
	AddObject(bg);
	/*//text
	GameObject* text=new GameObject();
	Text* newtxt=new Text((*text),"Recursos/font/Call me maybe.ttf", 100, Text::TextStyle::SOLID, "Press Space To Start", {255,255,255,255}, 1);
	text->AddComponent(newtxt);
	//CameraFollower* newflwr2=new CameraFollower(*text);
	//text->AddComponent(newflwr2);
	text->box.y=Camera::pos.y+400;
	text->box.x=Camera::pos.x+40;
	AddObject(text);*/
	//play button
	GameObject* pbutton = new GameObject();
	MenuButton* newpbutton = new MenuButton((*pbutton), (1124.0/1920.0)*1024.0, (450.0/1080.0)*576.0, (300.0/1920.0)*1024.0, (115.0/1080.0)*576.0, MenuButton::Type::PLAY);
	pbutton->AddComponent(newpbutton);
	AddObject(pbutton);
	//exit button
	GameObject* ebutton = new GameObject();
	MenuButton* newebutton = new MenuButton((*ebutton), (1124.0 / 1920.0)*1024.0, (780.0 / 1080.0)*576.0, (300.0 / 1920.0)*1024.0, (115.0 / 1080.0)*576.0, MenuButton::Type::EXIT);
	ebutton->AddComponent(newebutton);
	AddObject(ebutton);
	//tutorial button
	GameObject* tbutton = new GameObject();
	MenuButton* newtbutton = new MenuButton((*tbutton), (1124.0 / 1920.0)*1024.0, (615.0 / 1080.0)*576.0, (300.0 / 1920.0)*1024.0, (115.0 / 1080.0)*576.0, MenuButton::Type::TUTORIAL);
	tbutton->AddComponent(newtbutton);
	AddObject(tbutton);
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
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY) || MenuButton::exitButton){
		MenuButton::exitButton = false;
		quitRequested=true;
	}
	if(InputManager::GetInstance().QuitRequested()){
		quitRequested=true;
	}
	if(InputManager::GetInstance().KeyPress(SDLK_SPACE)||MenuButton::playButton){
		MenuButton::playButton = false;
		Game& game=Game::GetInstance();
		game.Push(new StageState());
	}
	if (MenuButton::tutorialButton) {
		MenuButton::tutorialButton = false;
		Game& game = Game::GetInstance();
		game.Push(new TutorialState());
	}
	Camera::pos.x=0;
	Camera::pos.y=0;
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
