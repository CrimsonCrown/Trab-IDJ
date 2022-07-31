#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"

State::State(){
	tileSet = new TileSet(64,64,"Recursos/img/tileset.png");
	quitRequested=false;
	LoadAssets();
	music.Play();
	return;
}

State::~State(){
	objectArray.clear();
	delete(tileSet);
}

bool State::QuitRequested(){
	return quitRequested;
}

void State::LoadAssets(){
	GameObject* bg=new GameObject();
	Sprite* newspr=new Sprite((*bg),"Recursos/img/ocean.jpg");
	bg->AddComponent(newspr);
	objectArray.emplace_back(bg);
	GameObject* map=new GameObject();
	TileMap* mapping=new TileMap((*map),"Recursos/map/tileMap.txt", tileSet);
	map->AddComponent(mapping);
	objectArray.emplace_back(map);
	music.Open("Recursos/audio/stageState.ogg");
	return;
}

void State::Update(float dt){
	if(InputManager::GetInstance().IsKeyDown(ESCAPE_KEY)){
		quitRequested=true;
	}
	if(InputManager::GetInstance().QuitRequested()){
		quitRequested=true;
	}
	if(InputManager::GetInstance().IsKeyDown(' ')){
		Vec2 objPos = ((Vec2( 200, 0 )).Rotate( -PI + PI*(rand() % 1001)/500.0 )).Add(Vec2( InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY() ));
		AddObject((int)objPos.x, (int)objPos.y);
	}
	long unsigned int index;
	for(index=0;index<objectArray.size();index++){
		objectArray[index]->Update(dt);
	}
	for(index=0;index<objectArray.size();index++){
		if(objectArray[index]->IsDead()){
			objectArray.erase(objectArray.begin()+index);
		}
	}
	//TODO: clisoes, entidades
	return;
}

void State::Render(){
	long unsigned int index;
	for(index=0;index<objectArray.size();index++){
		objectArray[index]->Render();
	}
	return;
}

void State::AddObject(int mouseX, int mouseY){
	GameObject* objToAdd=new GameObject();
	Sprite* newspr=new Sprite((*objToAdd),"Recursos/img/penguinface.png");
	objToAdd->box.x=mouseX-objToAdd->box.w/2;
	objToAdd->box.y=mouseY-objToAdd->box.h/2;
	objToAdd->AddComponent(newspr);
	Sound* newsnd=new Sound((*objToAdd),"Recursos/audio/boom.wav");
	objToAdd->AddComponent(newsnd);
	Face* newface=new Face((*objToAdd));
	objToAdd->AddComponent(newface);
	objectArray.emplace_back(objToAdd);
	return;
}