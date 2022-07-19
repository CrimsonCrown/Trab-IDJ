#ifndef MUSIC_INCLUDE
#define MUSIC_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>
#include "Resources.h"

class Music{
public:
	Music();
	Music(std::string file);
	~Music();
	void Play(int times=-1);
	void Stop(int msToStop=1500);
	void Open(std::string file);
	bool IsOpen();
private:
	Mix_Music* music;
};

#endif