#include "MenuButton.h"
#include "Sprite.h"

bool MenuButton::playButton;

MenuButton::MenuButton(GameObject& associated) : Component(associated){
	//cria sprite
	Sprite* newspr = new Sprite((associated), "Recursos/img/choromelo.png", 2, 1, 0, 0, 1, 0, 0);
	newspr->SetScaleX((120 / associated.box.w), (60 / associated.box.h));
	associated.AddComponent(newspr);
	//posiciona
	associated.box.x = 600;
	associated.box.y = 300;
	hovering = false;
	return;
}

void MenuButton::Update(float dt){
	if (associated.box.Contains({ (float)InputManager::GetInstance().GetMouseX() + Camera::pos.x, (float)InputManager::GetInstance().GetMouseY() + Camera::pos.y })) {
		if (hovering == false) {
			((Sprite*)associated.GetComponent("Sprite"))->SetAnim(1, 1, 0);
			hovering = true;
		}
		if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)) {
			//std::cout << "beep!\n";
			playButton = true;
		}
	}
	else {
		if (hovering) {
			((Sprite*)associated.GetComponent("Sprite"))->SetAnim(0, 0, 0);
			hovering = false;
		}
	}
	return;
}

void MenuButton::Render(){
	return;
}

bool MenuButton::Is(std::string type){
	if(type=="MenuButton"){
		return true;
	}
	return false;
}