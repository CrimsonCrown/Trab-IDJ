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
#include "Rat.h"
#include "HealthBar.h"
#include "NavMap.h"
#include "Wall.h"
#include "Bush.h"
#include "Pickup.h"
#include "SkillBar.h"
#include "PatrolSchedule.h"
#include "EndGate.h"
#include <fstream>

StageState::StageState(std::string mapfile, bool oldplayer, int oldhp, std::vector<Skill::Type> oldskills){
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
	//music
	music.Open("Recursos/audio/Tema_durante_o_jogo.mp3");
	//barulho inicial
	GameObject* bgin = new GameObject();
	//cria som
	Sound* newsnd = new Sound((*bgin), "Recursos/audio/cervo-grito-inicio.mp3");
	newsnd->Play(0);
	bgin->AddComponent(newsnd);
	newsnd = new Sound((*bgin), "Recursos/audio/ambiente-som-maluco.mp3");
	newsnd->Play(-1);
	bgin->AddComponent(newsnd);
	AddObject(bgin);
	//navigation
	GameObject* navigation = new GameObject();
	NavMap* newnavmap = new NavMap((*navigation),64,100,100);
	navigation->AddComponent(newnavmap);
	AddObject(navigation);

	//read file
	std::ifstream maptxt;
	char comma;
	int x,y,ex,ey;
	std::string tiles,walls,pickups,enemies,objects,sprites,next;
	maptxt.open(mapfile);
	maptxt >> x >> comma >> y >> ex >> comma >> ey >> tiles >> walls >> pickups >> enemies >> objects >> sprites >> next;
	maptxt.close();
	nextStage = next;

	//tile map
	GameObject* map=new GameObject();
	TileMap* mapping=new TileMap((*map),"Recursos/map/"+tiles+".txt", tileSet);
	map->AddComponent(mapping);
	AddObject(map);
	//end gate
	GameObject* endgate = new GameObject();
	EndGate* newgate = new EndGate((*endgate), 64, { ex,ey });
	endgate->AddComponent(newgate);
	AddObject(endgate);
	//walls
	LoadWalls("Recursos/map/"+walls+".txt");
	//pickup
	LoadPickups("Recursos/map/"+pickups+".txt");
	//patrols
	LoadPatrols("Recursos/map/"+enemies+".txt");
	//mushroom
	if(oldplayer){
		GameObject* shroom = new GameObject();
		Mushroom* newshroom = new Mushroom((*shroom), 64, { x,y }, oldhp, oldskills);
		shroom->AddComponent(newshroom);
		Camera::Follow(shroom);
		AddObject(shroom);
	}
	else {
		GameObject* shroom = new GameObject();
		Mushroom* newshroom = new Mushroom((*shroom), 64, { x,y });
		shroom->AddComponent(newshroom);
		Camera::Follow(shroom);
		AddObject(shroom);
	}
	//objects
	LoadObjects("Recursos/map/"+objects+".txt");
	//sprites
	LoadSprites("Recursos/map/" + sprites + ".txt");
	//end file
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
	else if(EndGate::ending){
		if (nextStage == "END") {
			GameData::playerVictory = true;
			popRequested = true;
			Game& game = Game::GetInstance();
			game.Push(new EndState());
		}
		else {
			popRequested = true;
			int hp = Mushroom::player->GetHp();
			std::vector<Skill::Type> types = Mushroom::player->GetSkillTypes();
			objectArray.clear();
			Game& game = Game::GetInstance();
			game.Push(new StageState("Recursos/map/"+nextStage+".txt",true,hp,types));
		}
	}
	return;
}

void StageState::Render(){
	RenderArray();
	return;
}

void StageState::Start(){
	music.Play();
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
	int x, y, sizex, sizey, ammountx, ammounty;
	std::string name;
	maptxt.open(file);
	/*int wallAmmount;
	maptxt >> wallAmmount;
	int i;
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
	}*/

	while (maptxt >> name) {
		maptxt >> x >> comma >> y >> comma >> sizex >> comma >> sizey >> comma >> ammountx >> comma >> ammounty >> comma;
		for (int w = 0; w < ammountx; w++) {
			for (int z = 0; z < ammounty; z++) {
				GameObject* wall = new GameObject();
				Wall* newwall = new Wall((*wall), { x + (w*sizex),y + (z*sizey) }, 64, sizex, sizey, "Recursos/img/" + name + ".png");
				wall->AddComponent(newwall);
				AddObject(wall);
			}
		}
	}
	maptxt.close();
	return;
}

void StageState::LoadPickups(std::string file) {
	std::ifstream maptxt;
	char comma;
	int x, y;
	std::string name;
	Pickup::Type type;
	maptxt.open(file);
	/*maptxt >> pickAmmount;
	int i;
	//std::cout << "trying to load walls\n";
	for (i = 0; i < pickAmmount; i++) {
		maptxt >> name >> x >> comma >> y >> comma;
		//std::cout << "trying to load " + name + " at " << x << " " << y << " sized " << sizex << " " << sizey << " in quantity " << ammountx << " " << ammounty << "\n";
		if (name == "MUFFLE") {
			type = Pickup::MUFFLE;
		}
		else if (name == "HEALTH") {
			type = Pickup::HEALTH;
		}
		else if (name == "SPEEDBOOST") {
			type = Pickup::SPEEDBOOST;
		}
		else if (name == "DASH") {
			type = Pickup::DASH;
		}
		else if (name == "DECOY") {
			type = Pickup::DECOY;
		}
		GameObject* pickup = new GameObject();
		Pickup* newpickup = new Pickup((*pickup), { x,y }, type, 64);
		pickup->AddComponent(newpickup);
		AddObject(pickup);
	}*/

	while (maptxt >> name) {
		maptxt >> x >> comma >> y >> comma;
		if (name == "MUFFLE") {
			type = Pickup::MUFFLE;
		}
		else if (name == "HEALTH") {
			type = Pickup::HEALTH;
		}
		else if (name == "SPEEDBOOST") {
			type = Pickup::SPEEDBOOST;
		}
		else if (name == "DASH") {
			type = Pickup::DASH;
		}
		else if (name == "DECOY") {
			type = Pickup::DECOY;
		}
		GameObject* pickup = new GameObject();
		Pickup* newpickup = new Pickup((*pickup), { x,y }, type, 64);
		pickup->AddComponent(newpickup);
		AddObject(pickup);
	}
	maptxt.close();
	return;
}

void StageState::LoadPatrols(std::string name) {
	std::vector<PatrolCommand> commands;
	std::ifstream patroltxt;
	char comma;
	int patrolAmmount;
	std::string patrolname;
	patroltxt.open(name);

	while (patroltxt >> patrolname) {
		patroltxt >> patrolAmmount;
		int x,y;
		float waittime;
		PatrolCommand cx;
		int i;
		for (i = 0; i < patrolAmmount; i++) {
			patroltxt >> x >> comma >> y >> comma >> waittime;
			cx.location = {x, y};
			cx.waitTime = waittime;
			commands.push_back(cx); 
		}
		if (patrolname == "enemy") {
			GameObject* enemy = new GameObject();
			Enemy* newenemy = new Enemy((*enemy), 64, commands);
			enemy->AddComponent(newenemy);
			enemy->box.x = commands.front().location.x * 64;
			enemy->box.y = commands.front().location.y * 64;
			AddObject(enemy);
		}
		if (patrolname == "rat") {
			GameObject* enemy = new GameObject();
			Rat* newrat = new Rat((*enemy), 64, commands);
			enemy->AddComponent(newrat);
			enemy->box.x = commands.front().location.x * 64;
			enemy->box.y = commands.front().location.y * 64;
			AddObject(enemy);
		}
		commands.clear();
	}
	
	patroltxt.close();
	return;
}

void StageState::LoadObjects(std::string name) {
	std::ifstream objectstxt;
	char comma;
	std::string objectname;
	objectstxt.open(name);

	while (objectstxt >> objectname) {
		int x,y;
		objectstxt >> x >> comma >> y;
		if (objectname == "bush") {
			//bush
			GameObject* bush = new GameObject();
			Bush* newbush = new Bush((*bush), TileCoords(x,y), 64, 1, 1);
			bush->AddComponent(newbush);
			AddObject(bush);
		}
	}
	objectstxt.close();
	return;
}

void StageState::LoadSprites(std::string file) {
	std::ifstream maptxt;
	char comma;
	int x, y, sizex, sizey, ammountx, ammounty;
	std::string name;
	maptxt.open(file);

	while (maptxt >> name) {
		maptxt >> x >> comma >> y >> comma >> sizex >> comma >> sizey >> comma >> ammountx >> comma >> ammounty >> comma;
		for (int w = 0; w < ammountx; w++) {
			for (int z = 0; z < ammounty; z++) {
				//cria sprite
				GameObject* sprite = new GameObject();
				Sprite* newspr = new Sprite((*sprite), "Recursos/img/" + name + ".png", 1, 1, 1000, 0, 1, 0, 0);
				newspr->SetScaleX((sizex*64 / sprite->box.w), (sizey*64 / sprite->box.h));
				sprite->box.x = (x*64) + (w*sizex*64);
				sprite->box.y = (y*64) + (z*sizey*64);
				sprite->AddComponent(newspr);
				AddObject(sprite);
			}
		}
	}
	maptxt.close();
	return;
}