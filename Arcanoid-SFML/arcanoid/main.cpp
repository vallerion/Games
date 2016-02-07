#include "Game.h"
#include <thread>

int main()
{
	Game *game = new Game();
	game->~Game();
	return 0;
}