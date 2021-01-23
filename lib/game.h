#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "apple.h"
#include "display.h"
#include "snake.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint8_t width;
	uint8_t height;
	apple_t *apple;
	snake_t *snake;
} game_t;

game_t *game_new(uint8_t width, uint8_t height);
void game_destroy(game_t *);

bool game_frame(game_t *);
void game_turn_right(game_t *);
void game_turn_left(game_t *);

bool game_reset(game_t *);

uint16_t game_score(game_t *);

game_display_t game_display(game_t *, uint8_t x, uint8_t y);

#endif