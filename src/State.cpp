#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "State.h"
#include "Collision.h"
#include "Collider.h"

State::State(){
	started=false;
	quitRequested=false;
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

State::~State(){
	objectArray.clear();
	delete(tileSet);
}

bool State::QuitRequested(){
	return quitRequested;
}

void State::LoadAssets(){
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
	Camera::Update(dt);
	long unsigned int index;
	long unsigned int indexaux;
	for(index=0;index<objectArray.size();index++){
		objectArray[index]->Update(dt);
	}
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

void State::Render(){
	long unsigned int index;
	for(index=0;index<objectArray.size();index++){
		objectArray[index]->Render();
	}
	return;
}

void State::AddObject(int mouseX, int mouseY){
	return;
}

void State::Start(){
	LoadAssets();
	long unsigned int index;
	for(index=0;index<objectArray.size();index++){
		objectArray[index]->Start();
	}
	started=true;
	return;
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
	//constroi shared ptr
	std::shared_ptr<GameObject> newobj(go);
	//coloca no vetor
	objectArray.push_back(newobj);
	//start caso necessario
	if(started){
		newobj->Start();
	}
	//retorna weak ptr
	std::weak_ptr<GameObject> newweak(newobj);
	return newweak;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
	//varre vetor
	long unsigned int index;
	for(index=0;index<objectArray.size();index++){
		if(objectArray[index].get()==go){
			std::weak_ptr<GameObject> newweak(objectArray[index]);
			return newweak;
		}
	}
	std::weak_ptr<GameObject> newweak;
	return newweak;
}