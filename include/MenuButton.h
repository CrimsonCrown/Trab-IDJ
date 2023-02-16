#ifndef MENUBUTTON_INCLUDE
#define MENUBUTTON_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"

class MenuButton : public Component{
public:
	enum Type { PLAY, PLAYENDWIN, PLAYENDLOSE, EXIT, EXITENDWIN, EXITENDLOSE, TUTORIAL, NEXT, BACK};
	MenuButton(GameObject& associated, int x, int y, int sizex, int sizey, Type bt);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	static bool tutorialButton;
	static bool playButton;
	static bool exitButton;
	static bool nextButton;
	static bool backButton;
private:
	std::string GetSprite();
	Type bt;
	bool hovering;
};

#endif