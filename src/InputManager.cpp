#include "InputManager.h"

void InputManager::Update(){
	SDL_Event event;
	updateCounter++;
	quitRequested=false;
	SDL_GetMouseState(&mouseX, &mouseY);
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		if(event.type==SDL_MOUSEBUTTONDOWN){
			mouseState[event.button.button]=true;
			mouseUpdate[event.button.button]=updateCounter;
		}
		if(event.type==SDL_MOUSEBUTTONUP){
			mouseState[event.button.button]=false;
			mouseUpdate[event.button.button]=updateCounter;
		}
		if(event.type==SDL_KEYDOWN){
			if(!event.key.repeat){
				if(event.key.keysym.sym>=0x40000000){
					keyState[event.key.keysym.sym-0x3FFFFF81]=true;
					keyUpdate[event.key.keysym.sym-0x3FFFFF81]=updateCounter;
				}
				else{
					keyState[event.key.keysym.sym]=true;
					keyUpdate[event.key.keysym.sym]=updateCounter;
				}
			}
		}
		if(event.type==SDL_KEYUP){
			if(event.key.keysym.sym>=0x40000000){
				keyState[event.key.keysym.sym-0x3FFFFF81]=false;
				keyUpdate[event.key.keysym.sym-0x3FFFFF81]=updateCounter;
			}
			else{
				keyState[event.key.keysym.sym]=false;
				keyUpdate[event.key.keysym.sym]=updateCounter;
			}
		}
	}
}

bool InputManager::KeyPress(int key){
	if(key>=0x40000000){
		if(keyUpdate[key-0x3FFFFF81]==updateCounter){
			return keyState[key-0x3FFFFF81];
		}
	}
	else{
		if(keyUpdate[key]==updateCounter){
			return keyState[key];
		}
	}
	return false;
}

bool InputManager::KeyRelease(int key){
	if(key>=0x40000000){
		if(keyUpdate[key-0x3FFFFF81]==updateCounter){
			if(!keyState[key-0x3FFFFF81]) return true;
		}
	}
	else{
		if(keyUpdate[key]==updateCounter){
			if(!keyState[key]) return true;
		}
	}
	return false;
}

bool InputManager::IsKeyDown(int key){
	if(key>=0x40000000){
		return keyState[key-0x3FFFFF81];
	}
	else{
		return keyState[key];
	}
	return false;
}

bool InputManager::MousePress(int button){
	if(mouseUpdate[button]==updateCounter){
		return mouseState[button];
	}
	return false;
}

bool InputManager::MouseRelease(int button){
	if(mouseUpdate[button]==updateCounter){
		return !mouseState[button];
	}
	return false;
}

bool InputManager::IsMouseDown(int button){
	return mouseState[button];
}

int InputManager::GetMouseX(){
	return mouseX;
}

int InputManager::GetMouseY(){
	return mouseY;
}

bool InputManager::QuitRequested(){
	return quitRequested;
}

InputManager& InputManager::GetInstance(){
	static InputManager inputManager;
	return inputManager;
}

InputManager::InputManager(){
	int i;
	for(i=0;i<6;i++){
		mouseState[i]=false;
		mouseUpdate[i]=0;
	}
	for(i=0;i<416;i++){
		keyState[i]=false;
		keyUpdate[i]=0;
	}
	quitRequested=false;
	updateCounter=0;
	mouseX=0;
	mouseY=0;
	return;
}

InputManager::~InputManager(){
	return;
}