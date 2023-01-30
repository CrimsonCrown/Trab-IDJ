#ifndef BUTTONTEXT_INCLUDE
#define BUTTONTEXT_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include <queue>

#include "Component.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include "TileCoords.h"

class ButtonText : public Component {
public:
	ButtonText(GameObject& associated, Vec2 position, int index);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
	Vec2 position;
	int index;
};

#endif