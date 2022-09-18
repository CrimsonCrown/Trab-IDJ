#include "Game.h"
#include "TitleState.h"

int main(int, char **){
	Game& game=Game::GetInstance();
	game.Push(new TitleState());
	game.Run();
	return 0;
}