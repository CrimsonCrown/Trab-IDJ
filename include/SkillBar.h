#ifndef SKILLBAR_INCLUDE
#define SKILLBAR_INCLUDE

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
#include "Minion.h"

class SkillBar : public Component {
public:
	SkillBar(GameObject& associated);
	~SkillBar();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	static SkillBar* bar;
	void AddIcon(int index);
private:
	Vec2 origin;
};

#endif