#include "Game.hpp"
#include "GameUtils.hpp"

int main()
{
	Game game(utils::width, utils::height, "aa");   //stack declaration, mobile viewport
	game.run();
	return 0;
}
