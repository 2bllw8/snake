#include "game.h"

#include <stdlib.h>

game_t *game_new(uint8_t width, uint8_t height)
{
	game_t *game = (game_t *)malloc(sizeof(game_t));
	if (!game) {
		return 0;
	}
	game->width = width;
	game->height = height;
	game->apple = apple_new(width, height);
	game->snake = snake_new(width / 2, height / 2, width, height);
	return game;
}

void game_destroy(game_t *game)
{
	if (!game) {
		return;
	}
	free(game->apple);
	snake_destroy(game->snake);
}

bool game_frame(game_t *game)
{
	if (!game || !game->snake || !game->apple) {
		return false;
	}

	bool step = snake_step(game->snake);
	if (step) {
		bool score_increased = apple_on_game_move(game->apple,
							  snake_x(game->snake),
							  snake_y(game->snake));
		if (score_increased) {
			snake_on_score_increased(game->snake);
		}
	}
	return step;
}

void game_turn_right(game_t *game)
{
	if (!game || !game->snake) {
		return;
	}
	snake_turn_right(game->snake);
}

void game_turn_left(game_t *game)
{
	if (!game || !game->snake) {
		return;
	}
	snake_turn_left(game->snake);
}

bool game_reset(game_t *game)
{
	if (!game) {
		return false;
	}

	apple_reset(game->apple);
	snake_destroy(game->snake);
	game->snake = snake_new(game->width / 2, game->height / 2, game->width,
				game->height);
	return true;
}

uint16_t game_score(game_t *game)
{
	return game && game->apple ? apple_score(game->apple) : 0;
}

game_display_t game_display(game_t *game, uint8_t x, uint8_t y)
{
	game_display_t snake = snake_display(game->snake, x, y);
	if (snake != DISPLAY_NONE) {
		return snake;
	}
	return apple_display(game->apple, x, y);
}
