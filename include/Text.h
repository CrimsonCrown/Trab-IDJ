#ifndef TEXT_INCLUDE
#define TEXT_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.h"
#include "GameObject.h"
#include "Resources.h"
#include "Timer.h"

class Text : public Component{
public:
	enum TextStyle{
		SOLID,
		SHADED,
		BLENDED
	};
	Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float period=0);
	~Text();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontFile(std::string fontFile);
	void SetFontSize(int fontSize);
private:
	void RemakeTexture();
	TTF_Font* font;
	SDL_Texture* texture;
	std::string text;
	TextStyle style;
	std::string fontFile;
	int fontSize;
	SDL_Color color;
	bool renderflag;
	float period;
	Timer timer;
};

#endif