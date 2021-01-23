#include "../cli/gui.h"
#include "../lib/game.h"

#define GAME_WIDTH 30
#define GAME_HEIGHT 10

int main(int argc, char **argv)
{
	game_t *game = game_new(GAME_WIDTH, GAME_HEIGHT);
	if (!game) {
		return 1;
	}

	run(game);
	game_destroy(game);
	return 0;
}
