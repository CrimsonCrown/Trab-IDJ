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
	Input();
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

void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = ((Vec2( 200, 0 )).Rotate( -PI + PI*(rand() % 1001)/500.0 )).Add(Vec2( mouseX, mouseY ));
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
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