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
#include "NavMap.h"
#include "Wall.h"
#include "Bush.h"
#include "Pickup.h"
#include "SkillBar.h"
#include <fstream>

StageState::StageState(){
	started=false;
	quitRequested=false;
	popRequested=false;
	//tile set
	tileSet = new TileSet(64,64,"Recursos/img/tile_copiar.png");
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
	//navigation
	GameObject* navigation = new GameObject();
	NavMap* newnavmap = new NavMap((*navigation),64,100,100);
	navigation->AddComponent(newnavmap);
	//newnavmap->Fill({ 5,5 }, 5, 1);
	//newnavmap->Fill({ 4,6 }, 2, 5);
	AddObject(navigation);
	//walls
	/*GameObject* wall = new GameObject();
	Wall* newwall = new Wall((*wall), {5,5}, 64, 1, 1);
	wall->AddComponent(newwall);
	AddObject(wall);
	wall = new GameObject();
	newwall = new Wall((*wall), { 6,5 }, 64, 1, 1);
	wall->AddComponent(newwall);
	AddObject(wall);
	wall = new GameObject();
	newwall = new Wall((*wall), { 7,5 }, 64, 1, 1);
	wall->AddComponent(newwall);
	AddObject(wall);
	wall = new GameObject();
	newwall = new Wall((*wall), { 8,5 }, 64, 1, 1);
	wall->AddComponent(newwall);
	AddObject(wall);
	wall = new GameObject();
	newwall = new Wall((*wall), { 9,5 }, 64, 1, 1);
	wall->AddComponent(newwall);
	AddObject(wall);
	wall = new GameObject();
	newwall = new Wall((*wall), { 13,8 }, 64, 1, 6);
	wall->AddComponent(newwall);
	AddObject(wall);*/
	LoadWalls("Recursos/map/wallMap.txt");
	//enemy
	GameObject* enemy = new GameObject();
	Enemy* newenemy = new Enemy((*enemy), 64);
	enemy->AddComponent(newenemy);
	enemy->box.x = 640;
	enemy->box.y = 576;
	AddObject(enemy);
	//mushroom
	GameObject* shroom=new GameObject();
	Mushroom* newshroom=new Mushroom((*shroom), 64);
	shroom->AddComponent(newshroom);
	shroom->box.x=704;
	shroom->box.y=640;
	Camera::Follow(shroom);
	AddObject(shroom);
	//bush
	GameObject* bush = new GameObject();
	Bush* newbush = new Bush((*bush), TileCoords(12,7), 64, 1, 1);
	bush->AddComponent(newbush);
	AddObject(bush);
	//pickup
	GameObject* pickup = new GameObject();
	Pickup* newpickup = new Pickup((*pickup), { 2,2 }, Pickup::MUFFLE, 64);
	pickup->AddComponent(newpickup);
	AddObject(pickup);
	pickup = new GameObject();
	newpickup = new Pickup((*pickup), { 4,2 }, Pickup::HEALTH, 64);
	pickup->AddComponent(newpickup);
	AddObject(pickup);
	pickup = new GameObject();
	newpickup = new Pickup((*pickup), { 6,2 }, Pickup::MUFFLE, 64);
	pickup->AddComponent(newpickup);
	AddObject(pickup);
	//health bar
	GameObject* hpbar=new GameObject();
	HealthBar* newbar=new HealthBar((*hpbar), 64);
	hpbar->AddComponent(newbar);
	AddObject(hpbar);
	//skill bar
	GameObject* skbar=new GameObject();
	SkillBar* newskbar=new SkillBar((*skbar));
	skbar->AddComponent(newskbar);
	AddObject(skbar);
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

void StageState::LoadWalls(std::string file) {
	std::ifstream maptxt;
	char comma;
	int wallAmmount;
	maptxt.open(file);
	maptxt >> wallAmmount;
	int x,y,sizex,sizey,ammountx,ammounty;
	int i;
	std::string name;
	//std::cout << "trying to load walls\n";
	for (i = 0; i < wallAmmount; i++) {
		maptxt >> name >> x >> comma >> y >> comma >> sizex >> comma >> sizey >> comma >> ammountx >> comma >> ammounty >> comma;
		//std::cout << "trying to load " + name + " at " << x << " " << y << " sized " << sizex << " " << sizey << " in quantity " << ammountx << " " << ammounty << "\n";
		for (int w=0; w < ammountx; w++) {
			for (int z=0; z < ammounty; z++) {
				GameObject* wall = new GameObject();
				Wall* newwall = new Wall((*wall), { x+(w*sizex),y+(z*sizey) }, 64, sizex, sizey, "Recursos/img/" + name + ".png");
				wall->AddComponent(newwall);
				AddObject(wall);
			}
		}
	}
	maptxt.close();
	return;
}