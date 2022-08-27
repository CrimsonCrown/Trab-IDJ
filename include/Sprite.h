#ifndef SPRITE_INCLUDE
#define SPRITE_INCLUDE

#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.h"
#include "GameObject.h"
#include "Resources.h"
#include "Camera.h"

class Sprite : public Component{
public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, std::string file, int frameCount=1, float frameTime=1);
	~Sprite();
	void Open(std::string file);
	void SetClip(int x, int y, int w, int h);
	void Render();
	void Render(int x, int y, int w, int h);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	void Update(float dt);
	bool Is(std::string type);
	void SetScaleX(float scaleX, float scaleY);
	Vec2 GetScale();
	float angle;
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	Vec2 scale;
	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
};

#endif