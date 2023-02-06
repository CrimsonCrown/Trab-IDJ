#ifndef ENDGATE_INCLUDE
#define ENDGATE_INCLUDE

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
#include "Skill.h"
#include "TileCoords.h"

class EndGate : public Component {
public:
	EndGate(GameObject& associated, float tileSize, TileCoords initialPosition);
	~EndGate();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	static bool ending;
	void NotifyCollision(GameObject& other);
	void Place(TileCoords position);
private:
	float tileSize;
};

#endif