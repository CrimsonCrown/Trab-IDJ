#ifndef SCREAMER_INCLUDE
#define SCREAMER_INCLUDE

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

class Screamer : public Component{
public:
	Screamer(GameObject& associated, float noiseRadius);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
    void CreateNoise(Vec2 position);
private:
	bool seeing;
    float noiseRadius;
};

#endif