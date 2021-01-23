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

/*
 * Make a new game
 */
game_t *game_new(uint8_t width, uint8_t height);

/*
 * Destroy a game
 */
void game_destroy(game_t *);

/*
 * Perform a game "frame"
 */
bool game_frame(game_t *);

/*
 * Perform the "turn right" action
 */
void game_turn_right(game_t *);

/*
 * Perform the "turn left" action
 */
void game_turn_left(game_t *);

/*
 * Reset the game to start a new one
 */
bool game_reset(game_t *);

/*
 * Obtain the game score
 */
uint16_t game_score(game_t *);

/*
 * Obtain display info for a given coordinate
 * It can be DISPLAY_APPLE, DISPLAY_SNAKE_HEAD, DISPLAY_SNAKE_TAIL
 * or DISPLAY_NONE
 */
game_display_t game_display(game_t *, uint8_t x, uint8_t y);

#endif