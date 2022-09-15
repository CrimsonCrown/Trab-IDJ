#include "Game.h"
#include "StageState.h"

int main(int, char **){
	Game& game=Game::GetInstance();
	game.Push(new StageState());
	game.Run();
	return 0;
}