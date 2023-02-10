#include "MenuButton.h"
#include "Sprite.h"

bool MenuButton::playButton=false;
bool MenuButton::exitButton=false;

MenuButton::MenuButton(GameObject& associated, int x, int y, int sizex, int sizey, Type bt) : Component(associated){
	this->bt = bt;
	//cria sprite
	Sprite* newspr = new Sprite((associated), GetSprite(), 2, 1, 0, 0, 1, 0, 0);
	newspr->SetScaleX((sizex / associated.box.w), (sizey / associated.box.h));
	associated.AddComponent(newspr);
	//posiciona
	associated.box.x = x;
	associated.box.y = y;
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
			if (bt == PLAY) {
				playButton = true;
			}
			else if (bt == EXIT) {
				exitButton = true;
			}
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

std::string MenuButton::GetSprite() {
	if (bt == PLAY) {
		return "Recursos/img/deertrial.png";
	}
	else if (bt == EXIT) {
		return "Recursos/img/rattrial.png";
	}
	return "";
}