#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "StageState.h"
#include "Collision.h"
#include "Collider.h"

StageState::StageState(){
	started=false;
	quitRequested=false;
	popRequested=false;
	//tile set
	tileSet = new TileSet(64,64,"Recursos/img/tileset.png");
	//background
	GameObject* bg=new GameObject();
	Sprite* newspr=new Sprite((*bg),"Recursos/img/ocean.jpg");
	CameraFollower* newflwr=new CameraFollower(*bg);
	bg->AddComponent(newspr);
	bg->AddComponent(newflwr);
	AddObject(bg);
	//tile map
	GameObject* map=new GameObject();
	TileMap* mapping=new TileMap((*map),"Recursos/map/tileMap.txt", tileSet);
	map->AddComponent(mapping);
	AddObject(map);
	//music
	music.Open("Recursos/audio/stageState.ogg");
	music.Play();
	//alien
	GameObject* alien=new GameObject();
	Alien* newalien=new Alien((*alien),0);
	alien->AddComponent(newalien);
	alien->box.x=512;
	alien->box.y=300;
	AddObject(alien);
	//penguins
	GameObject* pbody=new GameObject();
	PenguinBody* newpbody=new PenguinBody((*pbody));
	pbody->AddComponent(newpbody);
	pbody->box.x=704;
	pbody->box.y=640;
	Camera::Follow(pbody);
	AddObject(pbody);
	return;
}

StageState::~StageState(){
	objectArray.clear();
	delete(tileSet);
}

void StageState::LoadAssets(){
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

void StageState::Update(float dt){
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		popRequested=true;
	}
	if(InputManager::GetInstance().QuitRequested()){
		quitRequested=true;
	}
	Camera::Update(dt);
	long unsigned int index;
	long unsigned int indexaux;
	UpdateArray(dt);
	for(index=0;index<objectArray.size();index++){
		if(objectArray[index]->GetComponent("Collider")!=nullptr){
			for(indexaux=index;indexaux<objectArray.size();indexaux++){
				if(indexaux!=index){
					if(objectArray[indexaux]->GetComponent("Collider")!=nullptr){
						if(Collision::IsColliding(((Collider*)objectArray[index]->GetComponent("Collider"))->box,
							((Collider*)objectArray[indexaux]->GetComponent("Collider"))->box,
							(objectArray[index]->angleDeg/360)*2*PI,
							(objectArray[indexaux]->angleDeg/360)*2*PI)){
							objectArray[index]->NotifyCollision(*objectArray[indexaux]);
							objectArray[indexaux]->NotifyCollision(*objectArray[index]);

						}
					}
				}
			}
		}
	}
	for(index=0;index<objectArray.size();index++){
		if(objectArray[index]->IsDead()){
			objectArray.erase(objectArray.begin()+index);
		}
	}
	//TODO: clisoes, entidades
	return;
}

void StageState::Render(){
	RenderArray();
	return;
}

void StageState::Start(){
	LoadAssets();
	StartArray();
	started=true;
	return;
}

void StageState::Pause(){
	return;
}

void StageState::Resume(){
	return;
}
