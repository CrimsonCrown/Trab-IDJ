#ifndef RESOURCES_INCLUDE
#define RESOURCES_INCLUDE

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include <iostream>
#include <unordered_map>

class Resources{
public:
	static SDL_Texture* GetImage(std::string file);
	static void ClearImages();
	static Mix_Music* GetMusic(std::string file);
	static void ClearMusics();
	static Mix_Chunk* GetSound(std::string file);
	static void ClearSounds();
private:
	static void OpenImage(std::string file);
	static void OpenMusic(std::string file);
	static void OpenSound(std::string file);
	static std::unordered_map<std::string, SDL_Texture*> imageTable;
	static std::unordered_map<std::string, Mix_Music*> musicTable;
	static std::unordered_map<std::string, Mix_Chunk*> soundTable;
};

#endif