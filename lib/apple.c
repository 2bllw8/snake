#include "apple.h"

#include <stdlib.h>
#include <time.h>

struct apple_t {
	uint8_t x;
	uint8_t y;
	uint8_t max_x;
	uint8_t max_y;
	uint16_t score;
};

void _change_position(apple_t *apple)
{
	apple->x = rand() % apple->max_x;
	apple->y = rand() % apple->max_y;
}

apple_t *apple_new(uint8_t width, uint8_t height)
{
	apple_t *apple = (apple_t *)malloc(sizeof(apple_t));
	if (!apple) {
		return 0;
	}
	apple->max_x = width;
	apple->max_y = height;
	apple->score = 0;
	_change_position(apple);
	return apple;
}

void apple_reset(apple_t *apple)
{
	apple->score = 0;
	_change_position(apple);
}

uint16_t apple_score(apple_t *apple)
{
	return apple->score;
}

bool apple_on_game_move(apple_t *apple, uint8_t x, uint8_t y)
{
	if (!apple || x != apple->x || y != apple->y) {
		return false;
	}
	apple->score++;
	_change_position(apple);
	return true;
}

game_display_t apple_display(apple_t *apple, uint8_t x, uint8_t y)
{
	return apple && x == apple->x && y == apple->y ? DISPLAY_APPLE :
							       DISPLAY_NONE;
}
