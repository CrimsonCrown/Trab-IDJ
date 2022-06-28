#include "Game.h"

int main(int, char **){
	Game game=Game::GetInstance();
	game.Run();
	return 0;
}