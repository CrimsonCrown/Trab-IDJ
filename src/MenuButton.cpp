#include "MenuButton.h"
#include "Sprite.h"

bool MenuButton::playButton=false;
bool MenuButton::exitButton=false;
bool MenuButton::nextButton = false;
bool MenuButton::backButton = false;
bool MenuButton::tutorialButton = false;

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
			if (bt == PLAY || bt == PLAYENDWIN || bt == PLAYENDLOSE) {
				playButton = true;
			}
			else if (bt == EXIT || bt == EXITENDWIN || bt == EXITENDLOSE) {
				exitButton = true;
			}
			else if (bt == TUTORIAL) {
				tutorialButton = true;
			}
			else if (bt == NEXT) {
				nextButton = true;
			}
			else if (bt == BACK) {
				backButton = true;
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
		return "Recursos/img/botaoJogar.png";
	}
	else if (bt == EXIT) {
		return "Recursos/img/botaoSair.png";
	}
	else if (bt == PLAYENDWIN) {
		return "Recursos/img/botaoVitoria1.png";
	}
	else if (bt == EXITENDWIN) {
		return "Recursos/img/botaoVitoria2.png";
	}
	else if (bt == PLAYENDLOSE) {
		return "Recursos/img/botaoDerrota1.png";
	}
	else if (bt == EXITENDLOSE) {
		return "Recursos/img/botaoDerrota2.png";
	}
	else if (bt == TUTORIAL) {
		return "Recursos/img/botaoOutros.png";
	}
	else if (bt == NEXT) {
		return "Recursos/img/botaoOutros.png";
	}
	else if (bt == BACK) {
		return "Recursos/img/botaoOutros.png";
	}
	return "";
}