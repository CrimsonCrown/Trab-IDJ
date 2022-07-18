#ifndef SPRITE_INCLUDE
#define SPRITE_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.h"
#include "GameObject.h"

class Sprite : public Component{
public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, const char* file);
	~Sprite();
	void Open(const char* file);
	void SetClip(int x, int y, int w, int h);
	void Render();
	void Render(int x, int y, int w, int h);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	void Update(float dt){return;}
	bool Is(std::string type);
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
};

#endif