#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "StageState.h"
#include "Collision.h"
#include "Collider.h"
#include "GameData.h"
#include "EndState.h"
#include "Game.h"
#include "Enemy.h"
#include "HealthBar.h"

StageState::StageState(){
	started=false;
	quitRequested=false;
	popRequested=false;
	//tile set
	tileSet = new TileSet(64,64,"Recursos/img/tile_fungitive.png");
	//background
	GameObject* bg=new GameObject();
	Sprite* newspr=new Sprite((*bg),"Recursos/img/ocean.jpg");
	CameraFollower* newflwr=new CameraFollower(*bg);
	bg->AddComponent(newflwr);
	bg->AddComponent(newspr);
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
	/*for(int i=0;i<3;i++){
		GameObject* alien=new GameObject();
		Alien* newalien=new Alien((*alien),0, 2+((std::rand()%100)*0.03));
		alien->AddComponent(newalien);
		alien->box.x=std::rand() % 1408;
		alien->box.y=std::rand() % 1280;
		AddObject(alien);
	}*/
	//enemy
	GameObject* enemy = new GameObject();
	Enemy* newenemy = new Enemy((*enemy));
	enemy->AddComponent(newenemy);
	enemy->box.x = 640;
	enemy->box.y = 576;
	AddObject(enemy);
	//mushroom
	GameObject* shroom=new GameObject();
	Mushroom* newshroom=new Mushroom((*shroom));
	shroom->AddComponent(newshroom);
	shroom->box.x=704;
	shroom->box.y=640;
	Camera::Follow(shroom);
	AddObject(shroom);
	//health bar
	GameObject* hpbar=new GameObject();
	HealthBar* newbar=new HealthBar((*hpbar));
	hpbar->AddComponent(newbar);
	AddObject(hpbar);
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
	long unsigned int index;
	long unsigned int indexaux;
	UpdateArray(dt);
	Camera::Update(dt);
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
	if(Mushroom::player==nullptr){
		GameData::playerVictory=false;
		popRequested=true;
		Game& game=Game::GetInstance();
		game.Push(new EndState());
	}
	/*else if(Alien::alienCount==0){
		GameData::playerVictory=true;
		popRequested=true;
		Game& game=Game::GetInstance();
		game.Push(new EndState());
	}*/
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
