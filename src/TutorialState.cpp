#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "TutorialState.h"
#include "Game.h"
#include "Text.h"
#include "Camera.h"
#include "GameData.h"
#include "MenuButton.h"

TutorialState::TutorialState(int page){
	this->page = page;
	started=false;
	quitRequested=false;
	popRequested=false;
	//background
	GameObject* bg=new GameObject();
	Sprite* newspr=new Sprite((*bg),GetSprite());
	newspr->SetScaleX((1024 / bg->box.w), (576 / bg->box.h));
	CameraFollower* newflwr=new CameraFollower(*bg);
	bg->AddComponent(newspr);
	bg->AddComponent(newflwr);
	AddObject(bg);
	//next button
	if (page < maxpages) {
		GameObject* nbutton = new GameObject();
		MenuButton* newnbutton = new MenuButton((*nbutton), (1200.0 / 1920.0)*1024.0, (730.0 / 1080.0)*576.0, (420.0 / 1920.0)*1024.0, (150.0 / 1080.0)*576.0, MenuButton::Type::NEXT);
		nbutton->AddComponent(newnbutton);
		AddObject(nbutton);
	}
	//back button
	if (page > 1) {
		GameObject* bbutton = new GameObject();
		MenuButton* newbbutton = new MenuButton((*bbutton), (200.0 / 1920.0)*1024.0, (730.0 / 1080.0)*576.0, (420.0 / 1920.0)*1024.0, (150.0 / 1080.0)*576.0, MenuButton::Type::BACK);
		bbutton->AddComponent(newbbutton);
		AddObject(bbutton);
	}
	//exit button
	GameObject* ebutton = new GameObject();
	MenuButton* newebutton = new MenuButton((*ebutton), (200.0 / 1920.0)*1024.0, (200.0 / 1080.0)*576.0, (420.0 / 1920.0)*1024.0, (150.0 / 1080.0)*576.0, MenuButton::Type::EXIT);
	ebutton->AddComponent(newebutton);
	AddObject(ebutton);
	return;
}

TutorialState::~TutorialState(){
	objectArray.clear();
}

void TutorialState::LoadAssets(){
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

void TutorialState::Update(float dt){
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY) || MenuButton::exitButton){
		MenuButton::exitButton = false;
		popRequested = true;
	}
	if(InputManager::GetInstance().QuitRequested()){
		quitRequested=true;
	}
	if (MenuButton::nextButton){
		MenuButton::nextButton = false;
		popRequested = true;
		Game& game = Game::GetInstance();
		game.Push(new TutorialState(page+1));
	}
	if (MenuButton::backButton) {
		MenuButton::backButton = false;
		popRequested = true;
		Game& game = Game::GetInstance();
		game.Push(new TutorialState(page - 1));
	}
	Camera::pos.x=0;
	Camera::pos.y=0;
	UpdateArray(dt);
	return;
}

void TutorialState::Render(){
	RenderArray();
	return;
}

void TutorialState::Start(){
	LoadAssets();
	StartArray();
	started=true;
	return;
}

void TutorialState::Pause(){
	return;
}

void TutorialState::Resume(){
	return;
}


std::string TutorialState::GetSprite() {
	if (page==1) {
		return "Recursos/img/win.jpg";
	}
	if (page == 2) {
		return "Recursos/img/title.jpg";
	}
	if (page == 3) {
		return "Recursos/img/lose.jpg";
	}
	return "";
}